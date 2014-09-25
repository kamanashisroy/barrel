#!/bin/lua

local gpiohome = '/sys/class/gpio'
local gpio4 = gpiohome .. '/gpio4'
local dbfile = '/srv/http/.data/ZG9vcmxvY2s_/Y3Jvbg__/1'


function setupdoor(x) 
	local doorexport = io.open(x .. '/export', "w")
	if not doorexport then
		return
	end
	doorexport:write("4")
	doorexport:close()
	local doordir = io.open(x .. '/gpio4/direction', "w")
	if not doordir then
		return
	end
	doordir:write("out")
	doordir:close()
end
function opendoor(x) 
	local door = io.open(x .. '/value', "w")
	if not door then
		return
	end
	door:write("1")
	door:close()
end
function updatedb(content) 
	local dbfd = io.open(dbfile, "w")
	if not dbfd then
		return
	end
	for x in pairs(content) do
		dbfd:write(x .. " = " .. content[x] .. "\n")
	end
	dbfd:close()
end

function trimline1(s)
  return (s:gsub("^%s*(.-)%s*$", "%1"))
end

function readdb(content) 
	local dbfd = io.open(dbfile, "r")
	if not dbfd then
		return
	end
	while true do
		local ln = dbfd:read("*line")
		if ln == nil then break end
		local lntrm = trimline1(ln)
		if lntrm ~= "" then
			local key = lntrm:gsub("^([A-Za-z_]*) = .*$", "%1");
			local value = lntrm:gsub("^[A-Za-z_]* = (.*)$", "%1");
			content[key] = value;
		end
	end
	dbfd:close()
end

function cronjob() 
	local property = {}
	readdb(property)
	if (property["done"] == "0") then
		opendoor(gpio4)
		property["done"] = 1
		updatedb(property)
	end
end

setupdoor(gpiohome);

while(true) do
	os.execute("sleep " .. tonumber(2))
	cronjob();
end

