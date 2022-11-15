#include "ScriptManager.h"

#include <thread>
#include <mutex>

#include "Extender/util.h"

ScriptManager gScriptManager;

ScriptManager::ScriptManager()
{
    
}

ScriptManager::~ScriptManager()
{
    
}

bool ScriptManager::RegisterScriptFile(std::string file)
{
    Script* script = new Script();
    script->Init();

    if (!script->IsValid())
    {
        setLastError("Scripting module is invalid!");
        return false;
    }

    if (!script->Execute(file))
    {
        setLastError("Failed to execute script!");
        return false;
    }

    gScriptManager.mScripts[file] = script;

    return true;
}

void ScriptManager::CallOnBoardUpdate()
{
    for (auto const& it : mScripts)
    {
        it.second->CallOnBoardUpdate();
    }
}

void ScriptManager::CallOnKeyPress(int key)
{
    for (auto const& it : mScripts)
    {
        it.second->CallOnKeyPress(key);
    }
}

void ScriptManager::Shutdown()
{
    for (auto const& it : mScripts)
    {
        it.second->Shutdown();
    }
}
