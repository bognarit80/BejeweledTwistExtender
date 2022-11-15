#include "multitwist.h"

#include "../Hooks.h"

#include <Engine.h>
#include <Extender/util.h>
#include "mods.h"

namespace MultiTwistMod
{
    /*NAKEDDEF(checkForMatchesOverride)
    {
        __asm
        {
            cmp isMultiTwistEnabled, 1;
            jz disable;
            jmp goback;

		disable:
			setz cl;
			test cl, cl;
			mov[eax], cl;

        goback:
            push 0x6CFD64;
            ret;
        }
    }*/
}

void initMultiTwistMod(CodeInjection::FuncInterceptor* hook)
{
    /*inject_jmp(0x6CFD5D, reinterpret_cast<void*>(MultiTwistMod::checkForMatchesOverride));*/
    if (isMultiTwistEnabled) {
        inject_byte(0x7D7BA6, 0x5A); //increase FoV even more to differentiate screenshots
        inject_nops(0x6CFD5D, 3);
        printf("MultiTwist Mod Initialized!\n");
    }
    else
        printf("MultiTwist Mod Initialized, but is disabled in config!\n");
}