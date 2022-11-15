#include <Extender/FuncInterceptor.h>
#include "Engine.h"

/* Floating Point support not loaded fix */
int(__cdecl *original_IsNonwritableInCurrentImage)(int a1) = CInit::Engine_IsNonwritableInCurrentImage;
int __cdecl new_IsNonwritableInCurrentImage(int a1)
{
    return 1;
}

void fixFloatingPointSupport(CodeInjection::FuncInterceptor* hook)
{
    /* Floating Point support not loaded fix */
    original_IsNonwritableInCurrentImage = hook->intercept(CInit::Engine_IsNonwritableInCurrentImage, new_IsNonwritableInCurrentImage);
}
