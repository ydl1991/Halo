-- Lua Macro to Check
kRegister = 'LUA_REGISTER'
kRegisterBindToUnit = 'LUA_U_REGISTER'
kGetGlue = 'LUA_GETGLUE'
kSetGlue = 'LUA_SETGLUE'
kCustomGlue = 'LUA_CUSTOMGLUE'

-- Support different type
kGetterTypeMap = { float = 'lua_pushnumber', 
				   int = 'lua_pushinteger', 
			       string = 'lua_pushstring', 
			       bool = 'lua_pushboolean',
			       long = 'lua_pushinteger' }
kSetterTypeMap = { float = 'luaL_checknumber', 
				   int = 'luaL_checkinteger', 
			       string = 'luaL_checkstring', 
			       bool = 'luaL_checkinteger',
			       long = 'luaL_checklong' }

------------------------
--		Get Glue
------------------------
GetGlue = { m_functionName = '', m_memberType = '', m_memberName = '' }
function GetGlue:new(object)
	object = object or {}
	setmetatable(object, self)
	self.__index = self
	return object
end

function GetGlue:WriteToFile(file, class)
	file:write('	static int ', class.m_name, self.m_functionName, '(lua_State* pState)\n')
	file:write('	{\n')
	file:write('		auto pClass = reinterpret_cast<', class.m_name, '*>(lua_touserdata(pState, 1));\n')
	file:write('		lua_pop(pState, 1);\n')
	file:write('		', self.m_memberType, ' arg = pClass->', self.m_functionName, '();\n')
	file:write('		', kGetterTypeMap[self.m_memberType],'(pState, arg);\n')
	file:write('		return 1;\n')
	file:write('	}\n\n')
end

------------------------
--		Set Glue
------------------------
SetGlue = { m_functionName = '', m_memberType = '', m_memberName = '' }
function SetGlue:new(object)
	object = object or {}
	setmetatable(object, self)
	self.__index = self
	return object
end

function SetGlue:WriteToFile(file, class)
	file:write('	static int ', class.m_name, self.m_functionName, '(lua_State* pState)\n')
	file:write('	{\n')
	file:write('		auto pClass = reinterpret_cast<', class.m_name, '*>(lua_touserdata(pState, 1));\n')
	file:write('		', self.m_memberType,' arg = static_cast<', self.m_memberType, '>(', kSetterTypeMap[self.m_memberType], '(pState, 2));\n')
	file:write('		pClass->', self.m_functionName, '(arg);\n')
	file:write('		lua_pop(pState, 2);\n')
	file:write('		return 0;\n')
	file:write('	}\n\n')
end

------------------------
--	   Custom Glue
------------------------
CustomGlue = { m_functionName = '' }
function CustomGlue:new(object)
	object = object or {}
	setmetatable(object, self)
	self.__index = self
	return object
end

----------------------
-- Header File Class
----------------------
HeaderFile = { m_writeGenFile = false, m_fileName = '' }
function HeaderFile:new(object)
	local object = object or {}	-- if nothing passed in, create a new empty table
	self.m_classes = {}			-- table must be created inside function for each object cuz it's by reference
								-- otherwise you are only creating 1 table for all objects
	setmetatable(object, self)
	self.__index = self			-- if a key request cannot be found in object, search the key in the metatable
	return object
end

function HeaderFile:WriteGenFile()
	-- only write gen file if the class has a register macro
	if self.m_writeGenFile then
		
		-- % is an escape character so we can find the .
		local genFile = string.gsub(self.m_fileName, '%.h', '.gen');

		-- Log file name using regular express
		local s,_ = string.find(genFile, "\\[^\\]*$")
		LOG(string.format("Making Gen File - %s", string.sub(genFile, s + 1, -1)))
		
		local file = io.open(genFile, 'w');

		-- write include files
		file:write('#include "', genFile:sub(s + 1, -4),'h"\n');
		file:write('#include <ApplicationLayer/ApplicationLayer.h>\n');
		file:write('#include <GameLayer/Script/LuaScripter.h>\n\n');

		-- write aliases
		file:write('using namespace std;\n');
		file:write('using namespace halo;\n\n');

		-- write our intro
		file:write('namespace Lua\n');
		file:write('{\n');

		for i, class in ipairs(self.m_classes) do
			if class.m_writeLuaBindings then
				-- write our getters
				for i, getGlue in ipairs(class.m_getGlue) do
					getGlue:WriteToFile(file, class);
				end
				-- write our setters
				for i, setGlue in ipairs(class.m_setGlue) do
					setGlue:WriteToFile(file, class);
				end
			end
		end

		-- write our outro
		file:write('}\n\n');

		-- write our class register functions
		for i, class in ipairs(self.m_classes) do
			if (class.m_writeLuaBindings) then
				-- write function signiture and start
				file:write('void ', class.m_name, '::RegisterWithScript()\n');
				for i, line in ipairs(class.m_registerFunctionBodyStart) do
					file:write(line, '\n');
				end	
				
				-- write function body
				if class.m_gameUnitRelated then
					for i, line in ipairs(class.m_registerBindToGameUnit) do
						file:write(line, '\n');
					end
				end

				-- write getter
				for i, getGlue in ipairs(class.m_getGlue) do
					file:write('			pLuaScripter->AddToTable("', getGlue.m_functionName,
						'", Lua::', class.m_name, getGlue.m_functionName, ');\n');                
				end

				-- write setter
				for i, setGlue in ipairs(class.m_setGlue) do
					file:write('			pLuaScripter->AddToTable("', setGlue.m_functionName,
						'", Lua::', class.m_name, setGlue.m_functionName, ');\n');                
				end

				-- write our custom functions
				for i, customGlue in ipairs(class.m_customGlue) do
					file:write('			pLuaScripter->AddToTable("', customGlue.m_functionName,
						'", Lua::', class.m_name, customGlue.m_functionName, ');\n');                
				end

				-- write class representation and function end
				if class.m_gameUnitRelated then
					-- if game unit related
					file:write('			pLuaScripter->AddToTable("', class.m_name, '");\n');
					for i, line in ipairs(class.m_registerEndBindToGameUnit) do
						file:write(line, '\n');
					end
				else
					for i, line in ipairs(class.m_registerFunctionBodyEnd) do
						file:write(line, '\n');
					end
				end
			end
		end
	end
end

-- Function to Search Through Header File and Find Classes
kClassName = 'class'
function HeaderFile:ReadFile()
	local lines = {}

	-- Loop through the file name and Search line by line
	for line in io.lines(self.m_fileName) do
		table.insert(lines, line)
	end

	for lineIndex = 1, #lines do
		local words = GetWords(lines[lineIndex])

		-- Look for a Class
		for wordIndex, word in ipairs(words) do
			if word == kClassName then
				local class = Class:new({ m_name = words[wordIndex + 1] })
				lineIndex = class:Read(lines, lineIndex, self)
				table.insert(self.m_classes, class)
				break
			end
		end
	end
end

---------------------------
--		Class Class
---------------------------
Class = { m_writeLuaBindings = false, m_gameUnitRelated = false, m_name = '' }
-- register start
Class.m_registerFunctionBodyStart = {
	'{',
	'		auto pGameLayer = halo::ApplicationLayer::Get()->GetGameLayer();',
	'		if (auto pLuaScripter = pGameLayer->GetScripter<halo::LuaScripter>(); pLuaScripter)',
	'		{',
	'			pLuaScripter->GetGlobal("g_logic");',
}
-- register Bind to Game Unit
Class.m_registerBindToGameUnit = {
	'			pLuaScripter->RetrieveElementFromTable("GameUnits");',
	'			pLuaScripter->RetrieveElementFromTable(GetOwner()->GetID());',
	'			pLuaScripter->CreateTable();',
	'			pLuaScripter->AddToTable("this", this);',
}
-- register end
Class.m_registerFunctionBodyEnd = {
	'			pLuaScripter->PopAll();',
	'		}',
	'}',
}
Class.m_registerEndBindToGameUnit = {
	'			pLuaScripter->Pop(3);',
	'		}',
	'}',
}

function Class:new(object)
	local object = object or {}
	object.m_getGlue = {}
	object.m_setGlue = {}
	object.m_customGlue = {}
	setmetatable(object, self)
	self.__index = self
	return object
end

-- Class Read
function Class:Read(lines, startIndex, headerFile)
	for lineIndex = startIndex + 1, #lines do
		-- parse class
		local words = GetWords(lines[lineIndex])
		-- process words
		for wordIndex = 1, #words do
			local word = words[wordIndex]
			-- found class
			if word == kClassName then
				return lineIndex - 1		-- found the next class, so bail
			-- found lua register function
			elseif string.find(word, kRegister) then
				self.m_writeLuaBindings = true
				headerFile.m_writeGenFile = true
				LOG(string.format("Found Lua_Register for Class - %s", headerFile.m_fileName:sub(headerFile.m_fileName:find("\\[^\\]*$") + 1, -1)))
			elseif string.find(word, kRegisterBindToUnit) then
				self.m_writeLuaBindings = true
				self.m_gameUnitRelated = true
				headerFile.m_writeGenFile = true
				LOG(string.format("Found Lua_U_Register for Class - %s", headerFile.m_fileName:sub(headerFile.m_fileName:find("\\[^\\]*$") + 1, -1)))
			-- found getters
			elseif string.find(word, kGetGlue) then
				local getGlue = GetGlue:new({
					m_functionName = words[wordIndex + 1],
					m_memberType = words[wordIndex + 2],
					m_memberName = words[wordIndex + 3] 
				})
				table.insert(self.m_getGlue, getGlue)
			-- found setters
			elseif string.find(word, kSetGlue) then
				local setGlue = SetGlue:new({
					m_functionName = words[wordIndex + 1],
					m_memberType = words[wordIndex + 2],
					m_memberName = words[wordIndex + 3] 
				})
				table.insert(self.m_setGlue, setGlue)
			-- found custom functions
			elseif string.find(word, kCustomGlue) then
				local customGlue = CustomGlue:new({
					m_functionName = words[wordIndex + 1],
				})
				table.insert(self.m_customGlue, customGlue)
			end

		end
	end
	return #lines
end

-- Function to Get Words inside a line
function GetWords(line)
	local words = {}

	-- see if there is "//" in line
	local s, _ = string.find(line, "//")
	if s ~= nil then
		line = string.sub(line, 1, s - 1)
	end

	-- split by whitespace
	for word in line:gmatch("%S+") do
		-- split by non-alphanumeric
		for a in word:gmatch("[%w_]+") do
			table.insert(words, a)
		end
	end
	return words
end

-------------------------------------------------------------------------------------------
--									  Function Call
-------------------------------------------------------------------------------------------
-- Loop through each header file
for index, fileName in ipairs(g_headerFiles) do
	-- Log file name
	local s = string.find(fileName, "\\[^\\]*$")
	LOG(string.format("Parsing - %s", string.sub(fileName, s + 1, -1)))

	-- Create header file object
	header = HeaderFile:new({ m_fileName = fileName })
	-- header read and write
	header:ReadFile()
	header:WriteGenFile()
end