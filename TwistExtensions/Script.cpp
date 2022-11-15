#include "Script.h"

#include <lua.hpp>

#include "Extender/util.h"
#include "ScriptGameFunctions.h"

Script::Script() : mContext(nullptr), mValid(false)
{

}

Script::~Script() = default;


bool Script::Init()
{
    mLua = luaL_newstate();
    if (mLua == nullptr)
    {
        setLastError("Cannot create lua state: not enough memory");
        return false;
    }

    luaL_openlibs(mLua);

    ScriptGameFunctions::registerScriptFunctions(mLua);

    mValid = true;

    return true;
}

bool Script::Execute(const std::string& filename) const
{
    int status = luaL_loadfile(mLua, filename.c_str());
    if (status)
    {
        setLastError(std::string("Couldn't load file: ") + lua_tostring(mLua, -1));
        return false;
    }

    int result = lua_pcall(mLua, 0, LUA_MULTRET, 0);
    if (result)
    {
        setLastError(std::string("Failed to run script: ") + lua_tostring(mLua, -1));
        return false;
    }

    //lua_pop(mLua, 1);

    return true;
}

void Script::CallOnBoardUpdate() const
{
    int res = lua_getglobal(mLua, "onBoardUpdate");
    if (res == 0)
        return;

    if (lua_pcall(mLua, 0, 0, 0) != 0)
        printf_s("error running function `%s': %s\n", "onBoardUpdate", lua_tostring(mLua, -1));
}

void Script::CallOnKeyPress(int key) const
{
    int res = lua_getglobal(mLua, "onKeyPress");
    if (res == 0)
        return;
    lua_pushinteger(mLua, key);

    if (lua_pcall(mLua, 1, 0, 0) != 0)
        printf_s("error running function `%s': %s\n", "onKeyPress", lua_tostring(mLua, -1));
}

void Script::Shutdown()
{
    lua_close(mLua);
    mLua = nullptr;
}
