#include "crashfixmod.h"

#include <Engine.h>
#include <Extender/util.h>

namespace CrashFix
{
    bool IsValidPointer(void* ptr)
    {
        bool invalid = ptr == nullptr || reinterpret_cast<int>(ptr) < BJT_IMAGE_BASE || reinterpret_cast<unsigned int>(ptr) == 0xCCCCCCCC;
        //if (invalid)
        //    printf_s("Skip Invalid Ptr: ptr(0x%X)\n", reinterpret_cast<int>(ptr));
        return !invalid;
    }

    bool IsValidSkin(Sexy::Piece* piece)
    {
        return piece->skin >= Sexy::Piece::Skin::RED && piece->skin < Sexy::Piece::Skin::UNMATCHABLE;
    }

    bool IsValidImage(int* image)
    {
        bool valid = IsValidPointer(image) && (*image == 0x80e30c || *image == 0x80e224 || *image == 0x80e274);
        //if (!valid)
        //    printf_s("IsValidImage: 0x%p = 0x%X\n", image, *image);
        return valid;
    }

    NAKEDDEF(SkullFixImpl)
    {
        __asm
        {
            jz originalJz;

            pusha;
            mov eax, [ebx + 0x26CC];
            push eax;
            call IsValidPointer;
            cmp al, 0x00;
            jz pieceInvalid;
            pop eax;
            popa;

            push 0x6AAE2C;
            ret;

            pieceInvalid:
            pop eax;
            popa

            push 0x6AAF16;
            ret;

            originalJz:
            push 0x6AAF10;
            ret;
        }
    }

    NAKEDDEF(SkullFixImpl2)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call IsValidPointer;
            pop ecx;
            pop edx;
            cmp al, 0x00;
            pop eax;
            jz pieceInvalid;

            mov eax, [ecx + 0x28];
            cdq;
            idiv dword ptr[ecx + 0x2C];
            retn;

        pieceInvalid:;
            retn;
        }
    }

    NAKEDDEF(SkullFixImpl3)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call IsValidPointer;
            pop ecx;
            pop edx;
            cmp al, 0x00;
            pop eax;
            jz pieceInvalid;

            mov eax, [ecx + 0x24];
            cdq;
            idiv dword ptr[ecx + 0x30];
            retn;

        pieceInvalid:;
            retn;
        }
    }

    NAKEDDEF(SkullFixImpl4)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            call IsValidPointer;
            pop ecx;
            pop edx;
            cmp al, 0x00;
            pop eax;
            jz pieceInvalid;

            mov ebx, ecx;
            mov eax, [0x84E888];

            push 0x729B57;
            ret;

        pieceInvalid:;
            push 0x72AF54;
            ret;
        }
    }

    NAKEDDEF(SkullFixImpl6)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            push ebx;
            call IsValidPointer;
            pop ebx;
            pop ecx;
            pop edx;
            cmp al, 0x00;
            pop eax;
            jz pieceInvalid;

            mov[esp + 0x5C], edx;
            mov byte ptr[ebx + 0x04], 1;

            push 0x41A458;
            ret;

        pieceInvalid:;
            push 0x41C5BA;
            ret;
        }
    }

    NAKEDDEF(SkullFixImpl7)
    {
        __asm
        {
            mov eax, [ebp + 0xC];

            push edx;
            push ecx;
            push eax;
            call IsValidPointer;
            cmp al, 0x00;
            pop eax;
            pop ecx;
            pop edx;
            jz pieceInvalid;

            cmp dword ptr[eax + 0x1C], 0;

            push 0x70DCDB;
            ret;

        pieceInvalid:;
            push 0x70DD3C;
            ret;
        }
    }

    NAKEDDEF(NoSkinFixImpl)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            push ebx;
            call IsValidSkin;
            pop ebx;
            pop ecx;
            pop edx;
            cmp al, 0x00;
            pop eax;
            jz skinInvalid;

            // Original Code
            mov ecx, dword ptr ss:[0xE0B698];

            push 0x72A225;
            ret;

        skinInvalid:;
            mov[ebp - 0x1C], 0x00;
            push 0x72A2A3;
            ret;
        }
    }

    NAKEDDEF(NoSkinFix2Impl)
    {
        __asm
        {
            push eax;
            push edx;
            push ecx;
            push ebx;
            call IsValidImage;
            pop ebx;
            pop ecx;
            pop edx;
            cmp al, 0x00;
            pop eax;
            jz imageInvalid;

            // Original Code
            push 0x00;
            push 0x858E28;

            push 0x41A433;
            ret;

        imageInvalid:;
            push 0x41C59A;
            ret;
        }
    }
}

void initCrashFixMod(CodeInjection::FuncInterceptor* hook)
{
    printf("Crash Fix Mod Initialized!\n");

    inject_jmp(0x6AAE26, reinterpret_cast<void*>(CrashFix::SkullFixImpl));
    inject_jmp(0x423750, reinterpret_cast<void*>(CrashFix::SkullFixImpl2));
    inject_jmp(0x423760, reinterpret_cast<void*>(CrashFix::SkullFixImpl3));
    inject_jmp(0x729B50, reinterpret_cast<void*>(CrashFix::SkullFixImpl4));
    inject_jmp(0x41A450, reinterpret_cast<void*>(CrashFix::SkullFixImpl6));
    inject_jmp(0x70DCD4, reinterpret_cast<void*>(CrashFix::SkullFixImpl7));

    inject_jmp(0x72A21F, reinterpret_cast<void*>(CrashFix::NoSkinFixImpl));
    inject_jmp(0x41A42C, reinterpret_cast<void*>(CrashFix::NoSkinFix2Impl));

}
