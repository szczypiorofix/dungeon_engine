#include "LuaHandler.h"
#include "Defines.h"

LuaHandler::LuaHandler(const std::string& fileName) {
    std::string fn = DIR_SCRIPTS + fileName;
    luaState = luaL_newstate();
    luaL_openlibs(luaState);
    if (!loadFile(fn)) {
        std::cout << "Cannot read file: " << fn.c_str() << std::endl;
    }
}

LuaHandler::~LuaHandler() {
    this->close();
}

void LuaHandler::close() {
    if (!luaState)
        return;
    lua_close(luaState);
    luaState = nullptr;
}

bool LuaHandler::loadFile(const std::string fileName) {
    if (luaState && (fileName.length() > 0)) {
        luaL_loadfile(luaState, fileName.c_str());
        if (lua_pcall(luaState, 0, 0, 0) == LUA_OK)
            return true;
    }
    std::cout << lua_tostring(luaState, -1) << std::endl;
    return false;
}

bool LuaHandler::get(const char* name, int& value) {
    bool res = false;
    if (this->getGlobal(name) == false)
        return res;
    if (lua_isnumber(luaState, -1) == false) {
        lua_pop(luaState, 1);
        return res;
    }
    value = (int)(lua_tointeger(luaState, -1));
    lua_pop(luaState, 1);
    res = true;
    return res;
}

bool LuaHandler::get(const char* name, std::string& value) {
    if (this->getGlobal(name) == false)
        return false;
    if (lua_type(luaState, -1) != LUA_TSTRING) {
        lua_pop(luaState, 1);
        return false;
    }
    value = lua_tostring(luaState, -1);
    lua_pop(luaState, 1);
    return true;
}

bool LuaHandler::getGlobal(const char* name) {
    if ((!luaState) || (!name))
        return false;
    lua_getglobal(luaState, name);
    return true;
}
