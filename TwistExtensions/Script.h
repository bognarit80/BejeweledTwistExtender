#pragma once

#include <lua.hpp>

#include <string>

class Script
{
public:
    Script();
    virtual ~Script();

    bool Init();
    bool Execute(const std::string& filename) const;

    void CallOnBoardUpdate() const;
    void CallOnKeyPress(int key) const;

    void* getContext() const { return this->mContext; }
    bool IsValid() const { return this->mValid; }

    void Shutdown();

private:
    lua_State* mLua;
    void* mContext;
    bool mValid;
};
