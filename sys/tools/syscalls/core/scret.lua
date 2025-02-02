--
-- SPDX-License-Identifier: BSD-2-Clause
--
-- Copyright (c) 2024 Tyler Baxter <agge@FreeBSD.org>
-- Copyright (c) 2023 Warner Losh <imp@bsdimp.com>
-- Copyright (c) 2019 Kyle Evans <kevans@FreeBSD.org>
--

local util = require("tools.util")

local scret = {}

scret.__index = scret

-- Processes this return type.
function scret:process()
	local words = util.split(self.scret, "%S+")
	self.scret = words[1]
	if words[2]:find("%*") then
		local s1, s2 = util.splitPointer(words[2])
		-- We want to retrieve `void *foo` as `void *`, for any amount of
		-- pointers.
		self.scret = self.scret .. " " .. s1
	end
end

-- To add this return type to the system call.
function scret:add()
	self:process()
	return self.scret
end

function scret:new(obj, line)
	obj = obj or { }
	setmetatable(obj, self)
	self.__index = self

	self.scret = line

	return obj
end

return scret
