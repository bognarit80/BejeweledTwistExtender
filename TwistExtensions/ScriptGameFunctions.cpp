#include "ScriptGameFunctions.h"
#include "BejeweledTwist.h"

namespace ScriptGameFunctions
{

    int GetPieceSkinName(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("GetPieceSkinName: wrong number of arguments\n");
            return 0;
        }

        Sexy::Piece::Skin skin;

        if (lua_isinteger(lua, 1))
        {
            skin = static_cast<Sexy::Piece::Skin>(lua_tointeger(lua, 1));
        }
        else if (lua_isstring(lua, 1))
        {
            skin = BejeweledTwist::GetSkinByName(lua_tostring(lua, 1));
        }
        else
        {
            printf_s("GetPieceSkinName: invalid special argument\n");
            return 0;
        }

        std::string name = gBejeweledTwist->GetPieceSkinName(skin);

        lua_pushstring(lua, name.c_str());

        return 1;
    }

    int GetPieceSpecialName(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("GetPieceSpecialName: wrong number of arguments\n");
            return 0;
        }

        Sexy::Piece::SpecialType specialType;

        if (lua_isinteger(lua, 1))
        {
            specialType = static_cast<Sexy::Piece::SpecialType>(lua_tointeger(lua, 1));
        }
        else if (lua_isstring(lua, 1))
        {
            specialType = BejeweledTwist::GetSpecialByName(lua_tostring(lua, 1));
        }
        else
        {
            printf_s("GetPieceSpecialName: invalid special argument\n");
            return 0;
        }

        std::string name = gBejeweledTwist->GetPieceSpecialName(specialType);

        lua_pushstring(lua, name.c_str());

        return 1;
    }

    int GetRandomSkin(lua_State* lua)
    {
        Sexy::Piece::Skin skin = gBejeweledTwist->GetRandomSkin();

        lua_pushinteger(lua, static_cast<int>(skin));

        return 1;
    }

    int TwistGemsAt(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("TwistGemsAt: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isboolean(lua, 1) || !lua_isinteger(lua, 2) || !lua_isinteger(lua, 3))
        {
            printf_s("TwistGemsAt: invalid coordinate arguments\n");
            return 0;
        }

        bool fromScript = static_cast<bool>(lua_toboolean(lua, 1));
        int x = static_cast<int>(lua_tointeger(lua, 2));
        int y = static_cast<int>(lua_tointeger(lua, 3));

        gBejeweledTwist->TwistGemsAt(fromScript, x, y);

        return 1;
    }

    int GetHoverPos(lua_State* lua)
    {
        int x;
        int y;
        gBejeweledTwist->GetHoverPos(x, y);

        lua_newtable(lua);

        // x value
        lua_pushstring(lua, "x");
        lua_pushinteger(lua, x);
        lua_settable(lua, -3);

        // y value
        lua_pushstring(lua, "y");
        lua_pushinteger(lua, y);
        lua_settable(lua, -3);

        return 1;
    }

    int SetPieceSkin(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("SetPieceSkin: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("SetPieceSkin: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::Skin skin;

        if (lua_isinteger(lua, 3))
        {
            skin = static_cast<Sexy::Piece::Skin>(lua_tointeger(lua, 3));
        }
        else if (lua_isstring(lua, 3))
        {
            skin = BejeweledTwist::GetSkinByName(lua_tostring(lua, 3));
        }
        else
        {
            printf_s("SetPieceSkin: invalid skin argument\n");
            return 0;
        }

        gBejeweledTwist->SetPieceSkin(x, y, skin);

        return 1;
    }

    int GetPieceSkin(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 2)
        {
            printf_s("GetPieceSkin: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("GetPieceSkin: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::Skin skin = gBejeweledTwist->GetPieceSkin(x, y);

        lua_pushinteger(lua, static_cast<int>(skin));

        return 1;
    }

    int SetPieceSkinAtHover(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("SetPieceSkinAtHover: wrong number of arguments\n");
            return 0;
        }

        Sexy::Piece::Skin skin;

        if (lua_isinteger(lua, 1))
        {
            skin = static_cast<Sexy::Piece::Skin>(lua_tointeger(lua, 1));
        }
        else if (lua_isstring(lua, 1))
        {
            skin = BejeweledTwist::GetSkinByName(lua_tostring(lua, 1));
        }
        else
        {
            printf_s("SetPieceSkinAtHover: invalid skin argument\n");
            return 0;
        }

        gBejeweledTwist->SetPieceSkinAtHover(skin);

        return 1;
    }

    int SetPieceSpecial(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("SetPieceSpecial: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("SetPieceSpecial: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::SpecialType specialType;

        if (lua_isinteger(lua, 3))
        {
            specialType = static_cast<Sexy::Piece::SpecialType>(lua_tointeger(lua, 3));
        }
        else if (lua_isstring(lua, 3))
        {
            specialType = BejeweledTwist::GetSpecialByName(lua_tostring(lua, 3));
        }
        else
        {
            printf_s("SetPieceSpecial: invalid special argument\n");
            return 0;
        }

        gBejeweledTwist->SetPieceSpecial(x, y, specialType);

        return 1;
    }

    int SetPieceSpecialAtHover(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("SetPieceSpecialAtHover: wrong number of arguments\n");
            return 0;
        }

        Sexy::Piece::SpecialType specialType;

        if (lua_isinteger(lua, 1))
        {
            specialType = static_cast<Sexy::Piece::SpecialType>(lua_tointeger(lua, 1));
        } else if (lua_isstring(lua, 1))
        {
            specialType = BejeweledTwist::GetSpecialByName(lua_tostring(lua, 1));
        } else
        {
            printf_s("SetPieceSpecialAtHover: invalid special argument\n");
            return 0;
        }

        gBejeweledTwist->SetPieceSpecialAtHover(specialType);

        return 1;
    }

    int FillBoard(lua_State* lua)
    {
        gBejeweledTwist->FillBoard();

        return 1;
    }

    int ClearBoard(lua_State* lua)
    {
        gBejeweledTwist->ClearBoard();

        return 1;
    }

    /*int CheckPieceSpecial(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("CheckPieceSpecial: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("CheckPieceSpecial: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::SpecialType specialType;

        if (lua_isinteger(lua, 3))
        {
            specialType = static_cast<Sexy::Piece::SpecialType>(lua_tointeger(lua, 3));
        }
        else if (lua_isstring(lua, 3))
        {
            specialType = BejeweledTwist::GetSpecialByName(lua_tostring(lua, 3));
        }
        else
        {
            printf_s("CheckPieceSpecial: invalid special argument\n");
            return 0;
        }

        bool result = gBejeweledTwist->CheckSpecial(x, y, specialType);

        lua_pushboolean(lua, result);

        return 1;
    }*/

    int GetPieceSpecial(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 2)
        {
            printf_s("GetPieceSpecial: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("GetPieceSpecial: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::SpecialType type = gBejeweledTwist->GetSpecial(x, y);

        lua_pushinteger(lua, type);

        return 1;
    }

    int SetPieceCounter(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("SetPieceCounter: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("SetPieceCounter: invalid coordinate arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 3))
        {
            printf_s("SetPieceCounter: invalid counter argument\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));
        int counter = static_cast<int>(lua_tointeger(lua, 3));

        gBejeweledTwist->SetCounter(x, y, counter);

        return 1;
    }

    int GetPieceCounter(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 2)
        {
            printf_s("GetPieceCounter: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("GetPieceCounter: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        int counter = gBejeweledTwist->GetCounter(x, y);

        lua_pushinteger(lua, counter);

        return 1;
    }

    int SetPieceType(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("SetPieceType: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("SetPieceType: invalid coordinate arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 3))
        {
            printf_s("SetPieceType: invalid type argument\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));
        int type = static_cast<int>(lua_tointeger(lua, 3));

        gBejeweledTwist->SetPieceType(x, y, type);

        return 1;
    }

    int GetPieceType(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 2)
        {
            printf_s("GetPieceType: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("GetPieceType: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        int type = gBejeweledTwist->GetPieceType(x, y);

        lua_pushinteger(lua, type);

        return 1;
    }

    int SetPieceOldSkin(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("SetPieceOldSkin: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("SetPieceOldSkin: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::Skin skin;

        if (lua_isinteger(lua, 3))
        {
            skin = static_cast<Sexy::Piece::Skin>(lua_tointeger(lua, 3));
        }
        else if (lua_isstring(lua, 3))
        {
            skin = BejeweledTwist::GetSkinByName(lua_tostring(lua, 3));
        }
        else
        {
            printf_s("SetPieceOldSkin: invalid skin argument\n");
            return 0;
        }

        gBejeweledTwist->SetOldSkin(x, y, skin);

        return 1;
    }

    int GetPieceOldSkin(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 2)
        {
            printf_s("GetPieceOldSkin: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("GetPieceOldSkin: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        Sexy::Piece::Skin skin = gBejeweledTwist->GetOldSkin(x, y);

        lua_pushinteger(lua, static_cast<int>(skin));

        return 1;
    }

    int SetPieceMatchable(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 3)
        {
            printf_s("SetPieceMatchable: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("SetPieceMatchable: invalid coordinate arguments\n");
            return 0;
        }

        if (!lua_isboolean(lua, 3))
        {
            printf_s("SetPieceMatchable: invalid boolean argument\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));
        bool matchable = static_cast<int>(lua_toboolean(lua, 3));

        gBejeweledTwist->SetPieceMatchable(x, y, matchable);

        return 1;
    }

    int GetPieceMatchable(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 2)
        {
            printf_s("GetPieceMatchable: wrong number of arguments\n");
            return 0;
        }

        if (!lua_isinteger(lua, 1) || !lua_isinteger(lua, 2))
        {
            printf_s("GetPieceMatchable: invalid coordinate arguments\n");
            return 0;
        }

        int x = static_cast<int>(lua_tointeger(lua, 1));
        int y = static_cast<int>(lua_tointeger(lua, 2));

        bool matchable = gBejeweledTwist->GetPieceMatchable(x, y);

        lua_pushboolean(lua, matchable);

        return 1;
    }

    /*int IsInGame(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("IsInGame: wrong number of arguments\n");
            return 0;
        }

        int key = static_cast<int>(lua_tointeger(lua, 1));
        switch (key)
        {
        case 1:
            if (isMultiTwistEnabled)
                isMultiTwistEnabled = 0;
            else
                isMultiTwistEnabled = 1;
            break;
        case 2:
            if (isCCWEnabled)
                isCCWEnabled = 0;
            else
                isCCWEnabled = 1;
            break;
        case 3:
            if (altSound)
                altSound = 0;
            else
                altSound = 1;
            break;
        }


        return 1;
    }*/

    /*int IsCCWEnabled(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("IsCCWEnabled: wrong number of arguments\n");
            return 0;
        }

        isCCWEnabled = static_cast<bool>(lua_toboolean(lua, 1));

        return 1;
    }*/

    /*int IsMultiTwistEnabled(lua_State* lua)
    {
        int argc = lua_gettop(lua);
        if (argc < 1)
        {
            printf_s("IsMultiTwistEnabled: wrong number of arguments\n");
            return 0;
        }

        isMultiTwistEnabled = static_cast<int>(lua_tointeger(lua, 1));

        return 1;
    }*/

    void registerScriptFunctions(lua_State* lua)
    {
        lua_register(lua, "getPieceSkinName", GetPieceSkinName);
        lua_register(lua, "getPieceSpecialName", GetPieceSpecialName);
        lua_register(lua, "getRandomSkin", GetRandomSkin);
        lua_register(lua, "twistGemsAt", TwistGemsAt);
        lua_register(lua, "getHoverPos", GetHoverPos);
        lua_register(lua, "setPieceSkin", SetPieceSkin);
        lua_register(lua, "getPieceSkin", GetPieceSkin);
        lua_register(lua, "setPieceSkinAtHover", SetPieceSkinAtHover);
        lua_register(lua, "setPieceSpecial", SetPieceSpecial);
        lua_register(lua, "setPieceSpecialAtHover", SetPieceSpecialAtHover);
        lua_register(lua, "fillBoard", FillBoard);
        lua_register(lua, "clearBoard", ClearBoard);
        //lua_register(lua, "checkPieceSpecial", CheckPieceSpecial);
        lua_register(lua, "getPieceSpecial", GetPieceSpecial);
        lua_register(lua, "setPieceCounter", SetPieceCounter);
        lua_register(lua, "getPieceCounter", GetPieceCounter);
        lua_register(lua, "setPieceType", SetPieceType);
        lua_register(lua, "getPieceType", GetPieceType);
        lua_register(lua, "setPieceOldSkin", SetPieceOldSkin);
        lua_register(lua, "getPieceOldSkin", GetPieceOldSkin);
        lua_register(lua, "setPieceMatchable", SetPieceMatchable);
        lua_register(lua, "getPieceMatchable", GetPieceMatchable);
        /*lua_register(lua, "isMultiTwistEnabled", IsMultiTwistEnabled);*/
        /*lua_register(lua, "isInGame", IsInGame);*/
        /*lua_register(lua, "isCCWEnabled", IsCCWEnabled);*/
    }

    
}
