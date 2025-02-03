#!/usr/libexec/flua
--
-- SPDX-License-Identifier: BSD-2-Clause
--
-- Copyright (c) 2025 Tyler Baxter <agge@FreeBSD.org>
--

-- Add library root to the package path.
local path = arg[0]:gsub("/[^/]+.lua$", "")
package.path = package.path .. ";" .. path .. "/../?.lua"

local config = require("config")
local FreeBSDSyscall = require("core.freebsd-syscall")
local util = require("tools.util")
local generator = require("tools.generator")

local debug = true
local root = os.getenv("HOME") .. "/projects/freebsd-src"
local sysfile = root .. "/sys/kern/syscalls.master"
local configfile = root .. "/sys/kern/syscalls.conf"

-- Normalize tokens by removing unexpected characters (e.g., whitespace) and
-- splitting pointers attached to their operand into their own token. Returns
-- the normalized tokens.
-- Tokenize each line and normalize tokens into an
-- expected form.
local function processTokens(words)
	local new_words = {}
	for _, v in pairs(words) do
		-- Make sure v is a string so we can process it with string
		-- utilities.
		v = tostring(v)

		-- Strip whitespace and special whitespace. Strip commas too as
		-- they're only purpose is for argument lists (preserving
		-- doesn't matter for confirming our tokens match).
		v = v:gsub("[%s%c,]", "")

		-- xxx can have a better condition for if v is already split.
		if v ~= "*" and v ~= "**" and
		    (v:match("^%*+") or v:match("%*+$")) then
			-- Split pointers into separate tokens.
			local s1, s2 = util.splitPointer(v)
			table.insert(new_words, s1)
			table.insert(new_words, s2)
		else
		      table.insert(new_words, v)
		end
	end
	return new_words
end

local function typeToStr(sc)
	-- Filter out types that are FALSE.
	local types = {}
	for k, v in pairs(sc.type) do
		if v then
			table.insert(types, k)
		end
	end
	-- Create the type string (with pipe symbol in-between types).
	local type_str = ""
	-- We need to reverse iterate, because the order types are entered is
	-- (mostly) reverse alphabetical.
	for i = #types, 1, -1 do
		if i == 1 then
			type_str = type_str .. types[i]
		else
			type_str = type_str .. types[i] .. "|"
		end
	end
	return type_str
end

local function checkType(s1, s2, idx)
	local w1 = util.setFromString(s1, "[^|]+")
	local w2 = util.setFromString(s2, "[^|]+")

	for k, _ in pairs(w1) do
		if not w2[k] then
			print("Missing types at line " .. idx .. ".\n")
		end
	end
end

local function checkMatch(orig_words, new_words, idx)
	local fail = false
	for i = 1, #orig_words do
		-- Construct the debug strings first; it's okay
		-- if we index NIL in Lua.
		if orig_words[i] ~= new_words[i] then
			fail = true
		end
	end
	if fail then
		local orig_str = ""
		local new_str = ""
		for _, v in ipairs(orig_words) do
			orig_str = orig_str .. v .. " "
		end
		for _, v in ipairs(new_words) do
			new_str = new_str .. v .. " "
		end

		print("Token mismatch at line " .. idx .. ".")
		print("Expected: " .. orig_str)
		print("Actual:   " .. new_str .. "\n")
	end
end

-- This test works by reconstructing `syscalls.master`. We should be able to
-- reconstruct `syscalls.master` exactly to determine if we initially parsed it
-- correctly.
local function genScmasterNative(tbl)
	local s = tbl.syscalls
	local scmaster = {}

	for _,v in pairs(s) do
		local c = v:compatLevel()
		-- xxx hard-coding sysmux for now
		if v.num == 0 then
			table.insert(scmaster,
			    { "0", "AUE_NULL", "SYSMUX", "{" })
			table.insert(scmaster, { "int", "syscall(" })
			table.insert(scmaster, { "int", "number," })
			table.insert(scmaster, { "..." })
			table.insert(scmaster, { ");" })
			table.insert(scmaster, { "}" })
			goto skip
		elseif v.num == 198 then
			table.insert(scmaster,
			    { "198", "AUE_NULL", "SYSMUX", "{" })
			table.insert(scmaster, { "int", "__syscall(" })
			table.insert(scmaster, { "int64_t", "number," })
			table.insert(scmaster, { "..." })
			table.insert(scmaster, { ");" })
			table.insert(scmaster, { "}" })
			goto skip
		end


		local type_str = typeToStr(v)
		if type_str == "" then
			util.abort(1,
			    "System call should always have a type: " ..
			    v.name)
		end

		-- Starting line.
		if v.altname ~= nil and v.alttag ~= nil and
		    v.rettype ~= nil then
			table.insert(scmaster, {
			    v.num, v.audit, type_str, v.altname, v.alttag,
			    v.rettype
			})
		elseif v.type.OBSOL then
			table.insert(scmaster, {
			    v.num, v.audit, type_str, v.name })
		else
			table.insert(scmaster,
			    { v.num, v.audit, type_str, "{" })
		end

		if v.type.OBSOL or v.type.RESERVED or
		    v.type.UNIMPL or v.type.NODEF then
			-- One-line entry, skip it.
			goto skip
		end

		-- Function and arguments.
		if v.args == nil or #v.args < 1 then
			-- No arguments.
			table.insert(scmaster,
			    { v.ret, v.name .. "(void);" })
		else
			-- There is arguments.
			table.insert(scmaster, { v.ret, v.name .. "(" })

			--for _, sal in ipairs(v.sal) do
			--	table.insert(t, sal)
			--end

			for i, arg in ipairs(v.args) do
				local t = {}

				-- Insert SAL first, as defined in
				-- `syscalls.master`.
				for _, sal in pairs(arg.sal) do
					table.insert(t, sal)
				end

				-- Tokenize all `%S+` of the argument type.
				local w = util.split(arg.type, "%S+")
				for _, val in pairs(w) do
					table.insert(t,  val)
				end

				if i == #v.args then
					table.insert(t, arg.name)
				else
					table.insert(t, arg.name .. ",")
				end

				table.insert(scmaster, t)
			end

			table.insert(scmaster, { ");" })
		end

		-- Closing line.
		table.insert(scmaster, { "}" })

		::skip::
	end

	return scmaster
end

local function cmpScmasterNative(tbl)
	-- xxx change to be more integrated into make
	local fh = assert(io.open(sysfile, "r"))
	if not fh then
		print("ERROR: could not open " .. sysfile)
	end
	local scmaster = genScmasterNative(tbl)

	-- Keep track of ignores so we can have helpful error messages on the
	-- exact line number.
	local idx = 1

	-- Correction to properly index our generated `syscalls.master` buffer.
	local buf_idx = 1

	for line in fh:lines() do
		-- Ignore: blank lines, comments, C preprocessor directives,
		-- and ABI_HEADERS macro.
		if line == "" or line == nil or line:match("^;") or
		    line:match("^#") or line:match("^%%") then
			idx = idx - 1	-- continue

		-- Create duplicate lines if it's a range, so we can
		-- compare with our system call table correctly
		-- (a new system call is stored for each number of the
		-- range).
		elseif line:match("^%d+%-%d+") then
			local start, eend
			start, eend = line:match("^(%d+)%-(%d+)")
			start, eend = tonumber(start), tonumber(eend)
			local w = util.split(line, "%S+")
			while start <= eend do
				w[1] = start
				local orig_words = processTokens(w)
				local new_words = processTokens(scmaster[buf_idx])
				checkMatch(orig_words, new_words, idx)

				start = start + 1
				buf_idx = buf_idx + 1
			end

		-- We check the type separately, because there's no
		-- defined "order" for types.
		elseif line:match("^%d+%s+%S+") then
			local new_words = processTokens(scmaster[buf_idx])
			local orig_words = processTokens(
			    util.split(line, "%S+"))

			local nw = { new_words[1], new_words[2],
			    new_words[4] }
			local ow = { orig_words[1], orig_words[2],
			    orig_words[4] }

			checkMatch(ow, nw, idx)
			checkType(orig_words[3], new_words[3], idx)

			buf_idx = buf_idx + 1

		-- General case:
		else
			local new_words = processTokens(scmaster[buf_idx])
			local orig_words = processTokens(
			    util.split(line, "%S+"))
			checkMatch(orig_words, new_words, idx)

			buf_idx = buf_idx + 1
		end

		idx = idx + 1
	end

	fh:close()
end

-- Main entry:
if not debug then
	if #arg < 1 or #arg > 2 then
		error("usage: " .. arg[0] .. " syscall.master")
		sysfile, configfile = arg[1], arg[2]
	end
end

config.merge(configfile)
config.mergeCompat()

local tbl = FreeBSDSyscall:new({ sysfile = sysfile, config = config })

cmpScmasterNative(tbl)

-- vim: filetype=lua:noexpandtab:shiftwidth=8:tabstop=8:softtabstop=8:textwidth=80
