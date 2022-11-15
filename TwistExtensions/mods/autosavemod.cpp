#include "autosavemod.h"

#include "../Hooks.h"

#include <Engine.h>
#include <Extender/util.h>

void initAutosaveMod(CodeInjection::FuncInterceptor* hook)
{
    printf("Challenge & Blitz Autosave Mod Initialized!\n");

    inject_nops(0x6B3946, 1); //normally the function decreases mode number by 3, we skip one to make blitz count
    inject_byte(0x763AE0, 0xEB); //make blitz read save files by skipping a gamemode check
    inject_byte(0x724772, 0xEB); //make the small red bub appear below blitz if save exists, detail
    inject_byte(0x6A6AD9, 0xEB); //make challenge and blitz autosave by skipping a gamemode check
    inject_byte(0x6A6ADA, 0x18); //second part of above func
}