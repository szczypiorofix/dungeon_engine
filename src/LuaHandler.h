#ifndef _LUAHANDLER_H_
#define _LUAHANDLER_H_
#pragma once

#include <iostream>
#include <lua535/lua.hpp>


class LuaHandler {

public:
	LuaHandler(const std::string& fileName);
	~LuaHandler();

	void close();
	
	bool loadFile(const std::string fileName );

	bool get(const char* name, int& value);
	bool get(const char* name, std::string& value);

	bool getGlobal(const char* name);

private:
	lua_State* luaState;
	
};

#endif
