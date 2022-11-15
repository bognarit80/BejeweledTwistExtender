#include "coremod.h"

#include "../Hooks.h"

#include <Engine.h>
#include <Extender/util.h>

namespace CoreMod
{
    void onPreInitApp(Sexy::WinTwistApp* app)
    {
        return gHooks.callPreInitHooks(app);
    }

    void onPostInitApp(Sexy::WinTwistApp* app)
    {
        return gHooks.callPostInitHooks(app);
    }

    /// Called 60 times per second when in game
    void onUpdateBoard(Sexy::GameManager* gameManager)
    {
        return gHooks.callUpdateBoardHooks(gBejeweledTwist);
    }

    void onKeyPress(int key)
    {
        return gHooks.callBoardKeyPressHooks(gBejeweledTwist, key);
    }

    bool shouldAllowGemSelecting(Sexy::GameManager* gameManager)
    {
        return gHooks.callShouldAllowSelectionsHooks(gBejeweledTwist);
    }

    void onWindowInput(Sexy::WinTwistApp* app, int input)
    {
        return gHooks.callWindowInputHooks(app, input);
    }

    NAKEDDEF(preInitOverride)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call onPreInitApp;
            pop ecx;
            pop edx;
            pop eax;

            // Original Code
            xor ebx, ebx;
            cmp eax, ebx;
            mov esi, ecx;

            push 0x7652E6;
            ret;
        }
    }

    NAKEDDEF(postInitOverride)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call onPostInitApp;
            pop ecx;
            pop edx;
            pop eax;

            // Original Code
            mov eax, 0x43C180;
            call eax;

            push 0x765DFE;
            ret;
        }
    }

    NAKEDDEF(updateBoardOverride)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call onUpdateBoard;
            pop ecx;
            pop edx;
            pop eax;

            // Original Code
            mov eax, [ebx + 0x34EC];

            push 0x6D0926;
            ret;
        }
    }

    NAKEDDEF(onKeyPressOverride)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            mov eax, [esp + 0x10];
            push eax;
            call onKeyPress;
            pop eax;
            pop ecx;
            pop edx;
            pop eax;

            mov ecx, [ecx + 0x88];

            push 0x4C45A2;
            ret;
        }
    }

    NAKEDDEF(allowGemSelectOverride)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call shouldAllowGemSelecting;
            pop ecx;
            pop edx;
            cmp al, 0;
            pop eax;
            jnz allowGemSelecting;

            // Original Code
            push 0x6BD9CB;
            ret;

        allowGemSelecting:;

            // Original Code
            push[ebp + 0xC];
            mov esi, ecx;

            push 0x6BD9B7;
            ret;
        }
    }

    NAKEDDEF(windowInputOverride)
    {
        __asm
        {
            mov edi, [esp + 0x48];

            push eax;
            push edx;
            push ecx;
            push edi;
            push ebx;
            call onWindowInput;
            pop ebx;
            pop edi;
            pop ecx;
            pop edx;
            pop eax;

            cmp byte ptr[ebx + 0x518], 0;
            jz doRet;

            push 0x4A0F28;
            ret;

        doRet:;
            push 0x4A1284;
            ret;
        }
    }
}

void initCoreMod(CodeInjection::FuncInterceptor* hook)
{
    printf("Core Mod Initialized!\n");

    inject_jmp(0x7652E0, reinterpret_cast<void*>(CoreMod::preInitOverride));
    inject_jmp(0x765DF9, reinterpret_cast<void*>(CoreMod::postInitOverride));

    inject_jmp(0x6D0920, reinterpret_cast<void*>(CoreMod::updateBoardOverride));
    inject_jmp(0x6BD9B2, reinterpret_cast<void*>(CoreMod::allowGemSelectOverride));
    inject_jmp(0x4C459C, reinterpret_cast<void*>(CoreMod::onKeyPressOverride));
    inject_jmp(0x4A0F17, reinterpret_cast<void*>(CoreMod::windowInputOverride));

    //hide signature check error
    inject_byte(0x004A39C7, 0xE9);
    inject_byte(0x004A39C8, 0x86);
    inject_byte(0x004A39C9, 0x01);
    inject_byte(0x004A39CA, 0x00);
}
