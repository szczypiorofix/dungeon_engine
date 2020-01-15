#include "LuaHandler.h"
#include "Defines.h"


#define PLoo "PL"



LuaHandler::LuaHandler(const std::string& fileName) {
    std::string fn = DIR_SCRIPTS + fileName;
    this->luaState = luaL_newstate();
    luaL_openlibs(this->luaState);
    if (!loadFile(fn)) {
        std::cout << "Cannot read file: " << fn.c_str() << std::endl;
    }
}

LuaHandler::~LuaHandler() {
    close();
}

void LuaHandler::close() {
    if (!this->luaState)
        return;
    lua_close(this->luaState);
    this->luaState = nullptr;
}

bool LuaHandler::loadFile(const std::string fileName) {
    if (this->luaState && (fileName.length() > 0)) {
        luaL_loadfile(this->luaState, fileName.c_str());
        if (lua_pcall(this->luaState, 0, 0, 0) == LUA_OK)
            return true;
    }
    std::cout << lua_tostring(this->luaState, -1) << std::endl;
    return false;
}

bool LuaHandler::get(const char* name, int& value) {
    bool res = false;
    if (!this->getGlobal(name))
        return res;
    if (lua_isnumber(this->luaState, -1) == false) {
        lua_pop(this->luaState, 1);
        return res;
    }
    value = (int)(lua_tointeger(this->luaState, -1));
    lua_pop(this->luaState, 1);
    res = true;
    return res;
}

bool LuaHandler::get(const char* name, std::string& value) {
    if (!this->getGlobal(name))
        return false;
    if (lua_type(this->luaState, -1) != LUA_TSTRING) {
        lua_pop(this->luaState, 1);
        return false;
    }
    value = lua_tostring(this->luaState, -1);
    lua_pop(this->luaState, 1);
    return true;
}

bool LuaHandler::get(const char* name, PL& value)
{
    if (!this->getGlobal(name))
        return false;
    value = *(PL*)(lua_topointer(this->luaState, -1));
    lua_pop(this->luaState, 1);
    return true;
}

bool LuaHandler::getGlobal(const char* name) {
    if ((!this->luaState) || (!name))
        return false;
    lua_getglobal(this->luaState, name);
    return true;
}
