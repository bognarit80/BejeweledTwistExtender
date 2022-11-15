#include "mods.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Extender/FuncInterceptor.h>
#include <../ScriptGameFunctions.h>
#include "coremod.h"
#include "crashfixmod.h"
#include "scriptingmod.h"
#include "ccwtwist.h"
#include "autosavemod.h"
#include "aspectratiofix.h"
#include "multitwist.h"

//default values if no config file
bool isMultiTwistEnabled = 0;
bool isCCWEnabled = 1;
bool isMouseInverted = 0;
int altSound = 0;
int aspectRatio = 0;
//this is just the default config file content
std::string content = "isMultiTwistEnabled = 0\n#HIGHLY EXPERIMENTAL AND VERY BUGGY! Change to 1 to enable Multi-Twist (being able to twist while other gems are in motion). This is 0 by default if the file is missing\n\nisCCWEnabled = 1\n#Change to 1 to enable Counter-Clockwise Twisting on right-click and enter (return) button. This is 1 by default if the file is missing\n\ninvertMouse = 0\n#When set to 1, left click/space will CCW twist, and right click/enter will CW\n\naltSound = 0\n#Enabling CCW gives you three options for the twisting sound:\n# 0 - valid CW matches will play the valid twist sound, regardless of the actual rotation direction.\n# 1 - CW twists will play the valid twist sound, while CCW twists will play the invalid twist sound, regardless of whether the twist has been valid or not\n# 2 - same as 1, but in reverse. CCW twists now play valid sound, CW twists play invalid.\n#This value is set to 0 by default if the file is missing\n\naspectRatio = 0\n# 0 = 16:10\n# 1 = 16:9\n# 2 = 2:1\n# 3 = 21:9\n# 4 = 24:10\n# 5 = 24:9 (8:3)\n# 6 = 32:10\n# 7 = 30.5:9 (highest supported by the game)\n# anything else (default) = 16:10\n# if -widescreen launch parameter is present, the game will apply 16:9 if aspectRatio value is set to 0 too";

//name of the config file to look for and create if doesn't exist
char cfgfilename[] = "config.ini";

void OpenConfig() 
{
    //create config file if it doesn't exist
    if (!std::filesystem::exists(cfgfilename)) {
        printf("Config file not found! Creating %s with default values...\n", cfgfilename);
        std::fstream writer;
        writer.open(cfgfilename, std::ios_base::app);
        writer.write(content.data(), content.size());
        writer.close();
    }
    //load config file
    std::ifstream cFile(cfgfilename);
    if (cFile.is_open())
    {
        std::string line;
        while (std::getline(cFile, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            if (line.empty() || line[0] == '#') //skip lines starting with #, they are comments
            {
                continue;
            }
            int delimiterPos = line.find("="); //split line at the = sign
            std::string name = line.substr(0, delimiterPos);
            int value = std::stoi(line.substr(delimiterPos + 1));

            if (name == "isMultiTwistEnabled")
                isMultiTwistEnabled = value;
            else if (name == "isCCWEnabled")
                isCCWEnabled = value;
            else if (name == "invertMouse")
                isMouseInverted = value;
            else if (name == "altSound")
            {
                if (value > 2 || value < 0) 
                {
                    printf_s("altSound value incorrect! Falling back to default...");
                    altSound = 0;
                }                    
                else
                    altSound = value;
            }             
			else if (name == "aspectRatio")
				aspectRatio = value;
        }
    }
    else
    {
        printf("Couldn't open config file for reading!\n");
    }
}

bool initMods(CodeInjection::FuncInterceptor* hook)
{
    printf("> Initializing Mods\n");

    OpenConfig();
    initCoreMod(hook);
    initCrashFixMod(hook);
    initScriptingMod(hook);
    initCCWTwistMod(hook);
    initAutosaveMod(hook);
    initAspectRatioFix(hook);
    initMultiTwistMod(hook);

    return true;
}
