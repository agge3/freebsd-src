--
-- SPDX-License-Identifier: BSD-2-Clause
--
-- Copyright (c) 2024 Tyler Baxter <agge@FreeBSD.org>
-- Copyright (c) 2023 Warner Losh <imp@bsdimp.com>
-- Copyright (c) 2019 Kyle Evans <kevans@FreeBSD.org>
--

local config = require("config")
local scarg = require("core.scarg")
local scret = require("core.scret")
local util = require("tools.util")

local syscall = {}

syscall.__index = syscall

syscall.known_flags = util.set {
	"STD",
	"OBSOL",
	"RESERVED",
	"UNIMPL",
	"NODEF",
	"NOARGS",
	"NOPROTO",
	"NOSTD",
	"NOTSTATIC",
	"CAPENABLED",
	"SYSMUX",
}

-- Native is an arbitrarily large number to have a constant and not
-- interfere with compat numbers.
local native = 1000000

--
-- Processes the thread flag for this system call.
-- RETURN: String thr, the appropriate thread flag
--
local function processThr(type)
    local str = "SY_THR_STATIC"
    for k, _ in pairs(type) do
        if k == "NOTSTATIC" then
            str = "SY_THR_ABSENT"
        end
    end
    return str
end

--
-- Processes the capability flag for this system call.
-- RETURN: String cap, "SYF_CAPENABLED" for capability enabled, "0" if not
--
local function processCap(name, prefix, type)
    local str = "0"
    local stripped = util.stripAbiPrefix(name, prefix)
    if config.capenabled ~= nil and (config.capenabled[name] ~= nil or
		config.capenabled[stripped] ~= nil) then
        str = "SYF_CAPENABLED"
    else
        for k, _ in pairs(type) do
            if k == "CAPENABLED" then
                str = "SYF_CAPENABLED"
            end
        end
    end
    return str
end

-- Check that this system call has a known type.
local function checkType(type)
	for k, _ in pairs(type) do
	    if not syscall.known_flags[k] and not
            k:match("^COMPAT") then
			util.abort(1, "Bad type: " .. k)
		end
	end
end

function syscall:processFlags()
	if config.obsol[self.name] then
		self.args = nil
		self.type.OBSOL = true
	end
	if config.unimpl[self.name] then
		self.type.UNIMPL = true
	end
	if self.noproto or self.type.SYSMUX then
		self.type.NOPROTO = true
	end
	if self.type.NODEF then
		self.audit = "AUE_NULL"
	end
end

-- If there are ABI changes from native, process this system call to match the
-- target ABI.
function syscall:processChangesAbi()
    -- First, confirm we want to uphold our changes_abi flag.
    if config.syscall_no_abi_change[self.name] then
        self.changes_abi = false
    end
	self.noproto = not util.isEmpty(config.abi_flags) and not self.changes_abi
    if config.abiChanges("pointer_args") then
        for _, v in ipairs(self.args) do
            if util.isPtrType(v.type) then
                if config.syscall_no_abi_change[self.name] then
                    print("WARNING: " .. self.name ..
                        " in syscall_no_abi_change, but pointers args are present")
                end
                self.changes_abi = true
                goto ptrfound
            end
	    end
		::ptrfound::
    end
	if config.syscall_abi_change[self.name] then
		self.changes_abi = true
	end
    if self.changes_abi then
        self.arg_prefix = config.abi_func_prefix
        self.prefix = config.abi_func_prefix
		self.noproto = false
    end
end

-- XXX Incomplete/unused.
-- Returns TRUE if prefix and arg_prefix are assigned; FALSE if they're left
-- unassigned. Relies on a valid changes_abi flag, so should be called AFTER
-- processChangesAbi().
function syscall:processPrefix()
    -- If there are ABI changes from native, assign the correct prefixes.
    if self.changes_abi then
        self.arg_prefix = config.abi_func_prefix
        self.prefix = config.abi_func_prefix
        return true
    end
    return false
end

-- Validate that we're not skipping system calls by comparing this system call
-- number to the previous system call number. Called higher up the call stack by
-- class FreeBSDSyscall.
function syscall:validate(prev)
    return prev + 1 == self.num
end

-- Return the compat prefix for this system call.
function syscall:compatPrefix()
	local c = self:compatLevel()
	if self.type.OBSOL then
		return "obs_"
	end
	if self.type.RESERVED then
		return "reserved #"
	end
	if self.type.UNIMPL then
		return "unimp_"
	end
	if c == 3 then
		return "o"
	end
	if c < native then
		return "freebsd" .. tostring(c) .. "_"
	end
	return ""
end

-- Return the symbol name for this system call.
function syscall:symbol()
	return self:compatPrefix() .. self.name
end

-- XXX Incomplete/unused.
-- Return the comment for this system call.
function syscall:comment()
    --local c = self:compatLevel()
    if self.type.OBSOL then
        return "/* obsolete " .. self.alias .. " */"
    end
    if self.type.RESERVED then
        return "/* reserved for local use */"
    end
    if self.type.UNIMPL then
        return "" -- xxx
    else
        return "/* " .. self.num .. " = " .. self.alias .. " */"
    end
end

--
-- Return the compatibility level for this system call.
-- 0 is obsolete
-- < 0 is this isn't really a system call we care about
-- 3 is 4.3BSD in theory, but anything before FreeBSD 4
-- >= 4 FreeBSD version this system call was replaced with a new version
--
function syscall:compatLevel()
	if self.type.UNIMPL or self.type.RESERVED or self.type.NODEF then
		return -1
	elseif self.type.OBSOL then
		return 0
	elseif self.type.COMPAT then
		return 3
	end
	for k, _ in pairs(self.type) do
		local l = k:match("^COMPAT(%d+)")
		if l ~= nil then
			return tonumber(l)
		end
	end
	return native
end

-- Adds the definition for this system call. Guarded by whether we already have
-- a system call number or not.
function syscall:addDef(line)
    if self.num == nil then
        local words = util.split(line, "%S+")
	    self.num = words[1]
	    self.audit = words[2]
	    self.type = util.setFromString(words[3], "[^|]+")
	    checkType(self.type)
	    self.name = words[4]
	    -- These next three are optional, and either all present or all absent
	    self.altname = words[5]
	    self.alttag = words[6]
	    self.rettype = words[7]
	    return true
    end
    return false
end

-- Adds the function declaration for this system call. If addDef() found an
-- opening curly brace, then we're looking for a function declaration.
function syscall:addFunc(line)
    if self.name == "{" then
        local words = util.split(line, "%S+")
	    -- Expect line is "type syscall(" or "type syscall(void);"
        if #words ~= 2 then
            util.abort(1, "Malformed line " .. line)
        end

	    local ret = scret:new({}, line)
        self.ret = ret:add()
		-- Don't clobber rettype set in the alt information
		if self.rettype == nil then
			self.rettype = "int"
        end

	    self.name = words[2]:match("([%w_]+)%(")
	    if words[2]:match("%);$") then
            -- now we're looking for ending curly brace
            self.expect_rbrace = true
	    end
        return true
    end
    return false
end

-- Adds the argument(s) for this system call. Once addFunc() assigns a name for
-- this system call, arguments are next in syscalls.master.
function syscall:addArgs(line)
	if not self.expect_rbrace then
	    if line:match("%);$") then
            self.expect_rbrace = true
            return true
	    end
	    local arg = scarg:new({}, line)
        -- We don't want to add this argument if it doesn't process.
        -- scarg:process() handles those conditions.
        if arg:process() then
            arg:append(self.args)
        end
		-- If this argument has ABI changes, set globally for this system call.
		self.changes_abi = self.changes_abi or arg:changesAbi()
        return true
    end
    return false
end

-- XXX Incomplete/unused.
-- Decides if the NOPROTO flag should be added to this system call. Should be
-- called after processChangesAbi() so that there is a valid changes_abi flag
-- (an invalid flag may assign an invalid NOPROTO flag).
local function processNoproto()
	-- xxx
end

-- Once we have a good syscall, add some final information to it.
function syscall:finalize()
	if self.name == nil then
		self.name = ""
    end

    -- These may be changed by processChangesAbi(), or they'll remain empty for
    -- native.
    self.prefix = ""
    self.arg_prefix = ""
    self:processChangesAbi()
	self:processFlags()

    -- These need to be done before modifying self.name.
    self.cap = processCap(self.name, self.prefix, self.type) -- capability flag
    self.thr = processThr(self.type) -- thread flag
	-- Preserve the original name as the alias.
    self.alias = self.name

    -- Assign argument alias.
    if self.arg_alias == nil and self.name ~= nil then
        -- argalias should be:
        --   COMPAT_PREFIX + ABI Prefix + funcname
		self.arg_alias  = self:compatPrefix() .. self.arg_prefix .. self.name ..
			"_args"
    elseif self.arg_alias ~= nil then
        self.arg_alias = self.arg_prefix .. self.arg_alias
    end

    -- An empty string would not want a prefix; in that case we want to keep the
    -- empty string.
    if self.name ~= nil and self.name ~= "" then
        self.name = self.prefix .. self.name
    end
end

-- Interface to add this system call to the master system call table.
-- The system call is built up one line at a time. The states describe the
-- current parsing state.
-- Returns TRUE when ready to add and FALSE while still parsing.
function syscall:add(line)
    if self:addDef(line) then
		return self:isAdded(line)
    end
    if self:addFunc(line) then
        return false -- Function added; keep going.
    end
    if self:addArgs(line) then
        return false -- Arguments added; keep going.
    end
    return self:isAdded(line) -- Final validation, before adding.
end

-- Returns TRUE if this system call was succesfully added. There's two entry
-- points to this function: (1) the entry in syscalls.master is one-line, or (2)
-- the entry is a full system call. This function handles those cases and
-- decides whether to exit early for (1) or validate a full system call for (2).
-- This function also handles cases where we don't want to add, and instead want
-- to abort.
function syscall:isAdded(line)
	-- This system call is a range - exit early.
	if tonumber(self.num) == nil then
		-- The only allowed types are RESERVED and UNIMPL.
		if not (self.type.RESERVED or self.type.UNIMPL) then
			util.abort(1, "Range only allowed with RESERVED and UNIMPL: " ..
				line)
		end
		self:finalize()
		return true
	-- This system call is a loadable system call - exit early.
    elseif self.altname ~= nil and self.alttag ~= nil and
           self.rettype ~= nil then
		self:finalize()
		return true
	-- This system call is only one line, and should only be one line (we didn't
	-- make it to addFunc()) - exit early.
	elseif self.name ~= "{"  and self.ret == nil then
		self:finalize()
		return true
	-- This is a full system call and we've passed multiple states to get here -
	-- final exit.
	elseif self.expect_rbrace then
	    if not line:match("}$") then
			util.abort(1, "Expected '}' found '" .. line .. "' instead.")
	    end
        self:finalize()
        return true
    end
    return false
end

-- Return TRUE if this system call is native.
-- NOTE: The other system call names are also treated as native, so that's why
-- they're being allowed in here.
function syscall:native()
    return self:compatLevel() == native or self.name == "lkmnosys" or
           self.name == "sysarch"
end

-- Make a shallow copy of `self` and replace the system call number with num
-- (which should be a number).
-- For system call ranges.
function syscall:shallowCopy(num)
	local obj = syscall:new()

	-- shallow copy
	for k, v in pairs(self) do
		obj[k] = v
	end
	obj.num = num	-- except override range
	return obj
end

-- Make a deep copy of the parameter object. Save copied tables in `copies`,
-- indexed by original table.
-- CREDIT: http://lua-users.org/wiki/CopyTable
-- For a full system call (the nested arguments table should be a deep copy).
local function deepCopy(orig, copies)
    copies = copies or {}
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        if copies[orig] then
            copy = copies[orig]
        else
            copy = {}
            copies[orig] = copy
            for orig_key, orig_value in next, orig, nil do
                copy[deepCopy(orig_key, copies)] = deepCopy(orig_value, copies)
            end
            setmetatable(copy, deepCopy(getmetatable(orig), copies))
        end
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

--
-- In syscalls.master, system calls come in two types: (1) a fully defined
-- system call with function declaration, with a distinct number for each system
-- call; or (2) a one-line entry, sometimes with a distinct number and sometimes
-- with a range of numbers. One-line entries are obsolete, reserved, etc. Ranges
-- are only allowed for reserved and unimplemented.
--
-- This function provides the iterator to traverse system calls by number. If
-- the entry is a fully defined system call with a distinct number, the iterator
-- creates a deep copy and captures any nested objects; if the entry is a range
-- of numbers, the iterator creates shallow copies from the start of the range
-- to the end of the range.
--
function syscall:iter()
	local s = tonumber(self.num)
	local e
	if s == nil then
		s, e = string.match(self.num, "(%d+)%-(%d+)")
        s, e = tonumber(s), tonumber(e)
		return function ()
			if s <= e then
				s = s + 1
				return self:shallowCopy(s - 1)
			end
		end
	else
		e = s
		self.num = s	-- Replace string with number, like the clones
		return function ()
			if s == e then
                local deep_copy = deepCopy(self)
				s = e + 1
                return deep_copy
			end
		end
	end
end

function syscall:new(obj)
	obj = obj or { }
	setmetatable(obj, self)
	self.__index = self

	self.expect_rbrace = false
    self.changes_abi = false
	self.args = {}
	self.noproto = false

	return obj
end

return syscall
