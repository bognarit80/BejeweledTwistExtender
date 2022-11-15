#pragma once

#include "Script.h"
#include <string>
#include <map>
#include <thread>
#include <vector>

class ScriptManager
{
public:
    ScriptManager();
    virtual ~ScriptManager();

    bool RegisterScriptFile(std::string file);

    void CallOnBoardUpdate();
    void CallOnKeyPress(int key);

private:
    void Shutdown();

public:
    std::map<std::string, Script*> mScripts;
};

extern ScriptManager gScriptManager;