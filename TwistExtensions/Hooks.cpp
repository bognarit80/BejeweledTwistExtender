#include "Hooks.h"

Hooks gHooks;

Hooks::Hooks() :
                mPreInitHooksCount(0),
                mPostInitHooksCount(0),
                mUpdateBoardHooksCount(0),
                mBoardKeyPressHooksCount(0),
                mShouldAllowSelectionsHooksCount(0),
                mWindowInputHooksCount(0)
{
    
}

Hooks::~Hooks() = default;

// ---------------------------
// Register Hooks
// ---------------------------

int Hooks::registerPreInitHook(PreInitHook preInit)
{
    mPreInitHooks[mPreInitHooksCount] = preInit;
    return mPreInitHooksCount++;
}

int Hooks::registerPostInitHook(PostInitHook postInit)
{
    mPostInitHooks[mPostInitHooksCount] = postInit;
    return mPostInitHooksCount++;
}

int Hooks::registerUpdateBoardHook(UpdateBoardHook updateBoard)
{
    mUpdateBoardHooks[mUpdateBoardHooksCount] = updateBoard;
    return mUpdateBoardHooksCount++;
}

int Hooks::registerBoardKeyPressHook(BoardKeyPressHook boardKeyPress)
{
    mBoardKeyPressHooks[mBoardKeyPressHooksCount] = boardKeyPress;
    return mBoardKeyPressHooksCount++;
}

int Hooks::registerShouldAllowSelectionsHook(ShouldAllowSelectionsHooks shouldAllowSelections)
{
    mShouldAllowSelectionsHooks[mShouldAllowSelectionsHooksCount] = shouldAllowSelections;
    return mShouldAllowSelectionsHooksCount++;
}

int Hooks::registerWindowInputHook(WindowInputHook windowInput)
{
    mWindowInputHooks[mWindowInputHooksCount] = windowInput;
    return mWindowInputHooksCount++;
}

// ---------------------------
// Unregister Hooks
// ---------------------------

void Hooks::removePreInitHook(int index)
{
    mPreInitHooks.erase(index);
}

void Hooks::removePostInitHook(int index)
{
    mPostInitHooks.erase(index);
}

void Hooks::removeUpdateBoardHook(int index)
{
    mUpdateBoardHooks.erase(index);
}

void Hooks::removeBoardKeyPressHook(int index)
{
    mBoardKeyPressHooks.erase(index);
}

void Hooks::removeShouldAllowSelectionsHook(int index)
{
    mShouldAllowSelectionsHooks.erase(index);
}

void Hooks::removeWindowInputHook(int index)
{
    mWindowInputHooks.erase(index);
}

void Hooks::callPreInitHooks(Sexy::WinTwistApp* app)
{
    for (auto const& it : mPreInitHooks)
    {
        it.second(app);
    }
}

void Hooks::callPostInitHooks(Sexy::WinTwistApp* app)
{
    for (auto const& it : mPostInitHooks)
    {
        it.second(app);
    }
}

void Hooks::callUpdateBoardHooks(BejeweledTwist* game)
{
    for (auto const& it : mUpdateBoardHooks)
    {
        it.second(game);
    }
}

void Hooks::callBoardKeyPressHooks(BejeweledTwist* game, int key)
{
    for (auto const& it : mBoardKeyPressHooks)
    {
        it.second(game, key);
    }
}

bool Hooks::callShouldAllowSelectionsHooks(BejeweledTwist* game)
{
    bool forced = false;
    bool ret = true;

    for (auto const& it : mShouldAllowSelectionsHooks)
    {
        bool localForce = false;
        bool allow = it.second(game, localForce);
        if (!forced)
        {
            if (localForce)
            {
                ret = allow;
                forced = true;
            }
            else
            {
                ret = allow;
            }
        }
    }

    return ret;
}

void Hooks::callWindowInputHooks(Sexy::WinTwistApp* app, int input)
{
    for (auto const& it : mWindowInputHooks)
    {
        it.second(app, input);
    }
}
