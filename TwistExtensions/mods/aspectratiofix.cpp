#include "aspectratiofix.h"

#include "../Hooks.h"

#include <Engine.h>
#include <Extender/util.h>
#include "mods.h"
#include <Windows.h>
#include <processenv.h>

const char* widearg = " \" -widescreen";
namespace aspectRatioFix
{
	NAKEDDEF(DoParseCmdLineOverride)
	{
		__asm
		{
			mov eax, dword ptr[widearg];

			add esp, 8;
			test eax, eax;

			push 0x4A46F6;
			ret;
		}

	}
}

void initAspectRatioFix(CodeInjection::FuncInterceptor* hook)
{
	printf("Widescreen Mod Initialized! ");
	std::string cmdLine = GetCommandLine();

	//aspectRatio config can be set from 1 to 7, with each number being wider than the previous
	//if it's correctly set, -widescreen will be appended to the launch parameters for the ingame parser
	//if it's set to anything else, fall back to the default 16:10 resolution and return from the func
	//BUT, if the -widescreen launch parameter is already present (input by user)
	//the game will run 16:9 if the aspectRatio value is 0
	//this is done for users who just had a shortcut with -widescreen and don't understand this config thing
	switch (aspectRatio)
		{
		case 0: //16:10
		{
			if (cmdLine.find("-widescreen") != std::string::npos) 
			{
				//if -widescreen is already present switch to 16:9
				inject_byte(0x763527, 0x60);
				printf("Found -widescreen, aspect ratio: 16:9\n");
			}
			else
			{
				printf("Aspect ratio: 16:10 (Default)\n");
			}
			break;
		}
		case 1: //16:9
		{
			inject_byte(0x763527, 0x60);
			printf("Aspect ratio: 16:9\n");
			break;
		}
		case 2: //2:1
		{
			inject_byte(0x763527, 0x1C);
			printf("Aspect ratio: 2:1\n");
			break;
		}
		case 3: //21:9
		{
			inject_byte(0x763527, 0xC7);
			inject_byte(0x763528, 0x01);
			printf("Aspect ratio: 21:9\n");
			break;
		}
		case 4: //24:10
		{
			inject_byte(0x763527, 0xC2);
			inject_byte(0x763528, 0x01);
			printf("Aspect ratio: 24:10\n");
			break;
		}
		case 5: //24:9
		{
			inject_byte(0x763527, 0x95);
			inject_byte(0x763528, 0x01);
			printf("Aspect ratio: 24:9\n");
			break;
		}
		case 6: //32:10
		{
			inject_byte(0x763527, 0x51);
			inject_byte(0x763528, 0x01);
			printf("Aspect ratio: 32:10\n");
			break;
		}
		case 7: //30.5:9 (max supported by the game)
		{
			inject_byte(0x763527, 0x3D);
			inject_byte(0x763528, 0x01);
			printf("Aspect ratio: 30.5:9\n");
			break;
		}
		default: //16:10
		{
			inject_byte(0x763527, 0x60);
			printf("Invalid parameter passed, using default values...\n");
			return;
		}
		}
		inject_jmp(0x4A46F1, aspectRatioFix::DoParseCmdLineOverride);
}