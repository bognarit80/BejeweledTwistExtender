#include "scriptingmod.h"

#include "../Hooks.h"
#include "../ScriptManager.h"
#include "Extender/util.h"

#include <filesystem>
#include <regex>

namespace ScriptingMod
{
    void onPreInit(Sexy::WinTwistApp* app)
    {
        if (!std::filesystem::exists("data/scripts")) {
            std::filesystem::create_directories("data/scripts");
        }
        for (auto& p : std::filesystem::directory_iterator("data/scripts"))
        {
            std::wstring wpath = p.path().c_str();
            std::string path(wpath.begin(), wpath.end());
            path = std::regex_replace(path, std::regex("\\\\"), "/");
            std::string scriptPath = path + "/main.lua";
            
            if (fileExists(scriptPath))
            {
                printf_s("Loading Script File: %s\n", scriptPath.c_str());
                gScriptManager.RegisterScriptFile(scriptPath);
            }
        }
    }

    void onUpdateBoard(BejeweledTwist* game)
    {
        gScriptManager.CallOnBoardUpdate();
    }

    void onKeyPress(BejeweledTwist* game, int key)
    {
        gScriptManager.CallOnKeyPress(key);
    }

}

void initScriptingMod(CodeInjection::FuncInterceptor* hook)
{
    printf_s("Scripting Mod Initialized!\n");

    gHooks.registerPreInitHook(ScriptingMod::onPreInit);
    gHooks.registerUpdateBoardHook(ScriptingMod::onUpdateBoard);
    gHooks.registerBoardKeyPressHook(ScriptingMod::onKeyPress);
}
