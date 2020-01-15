#ifndef _LUAHANDLER_H_
#define _LUAHANDLER_H_
#pragma once

#include <iostream>
#include <lua535/lua.hpp>
#include <lua535/lauxlib.h>

typedef struct PL {
	int width;
	int height;
} PL;


class LuaHandler {

public:
	LuaHandler(const std::string& fileName);
	~LuaHandler();

	void close();
	
	bool loadFile(const std::string fileName );

	bool get(const char* name, int& value);
	bool get(const char* name, std::string& value);
	bool get(const char* name, PL& value);

	bool getGlobal(const char* name);

	PL* pl;

private:
	lua_State* luaState;
	
};

#endif
