#ifndef __ENGINE_H_
#define __ENGINE_H_

#include <Addresses.h>
#include <InterfaceMacros-win32.h>

namespace CInit
{
    FN(int, Engine_IsNonwritableInCurrentImage, (int a1), ADDR__IsNonwritableInCurrentImage);
}

namespace Sexy
{
    struct GameManager;

    struct InputStuff
    {
        int v1;
        int v2;
        int v3;
        int v4;
        int v5;
        int v6;
        int v7;
        int v8;
        int mouseY;
        int v10;
        int mouseX;
        int v12;
        int v13;
        int v14;
        int v15;
    };

    struct Piece
    {
        enum class Skin
        {
            RED = 0,
            WHITE = 1,
            GREEN = 2,
            YELLOW = 3,
            PURPLE = 4,
            ORANGE = 5,
            BLUE = 6,
            UNMATCHABLE = 7
        };

        enum SpecialType
        {
            NONE = 0,
            FRUIT = 1,
            SKULL = 2,
            LOCK = 4,
            LIGHTNING = 8,
            FLAME = 16,
            SUPERNOVA = 24,
            ICE = 64,
            ANGEL = 128,
            DOOM = 256,
            BOMB = 512,
            COAL = 1024
        };

        /*enum HazardType
        {
            DOOM = 1,
            BOMB = 2,
            COAL = 4
        };*/

        int _vftbl;
        int v1;
        Skin skin;
        int v4;

        int widthMaybe;
        int v5;
        int v6;
        int v7;
        int yPosMaybe;
        int v10;
        int xPosMaybe;
        char _gapNew3[88];
        int special;
        char _gapNew[100];
        int v66;
        float v77;
        int v88;
        char _gapNew4[8];
        int counter;
        char _gapNew6[392];
        Skin oldSkin;
        char _gapNew2[100];
        int v9;
        char _gapNew5[516];
        int pieceType;
        int unknown2;
        int unknown3;
        int unknown4;
        int unknown5;
        int unknown6;
        int unknown7;
        int special2;
        __int16 unknown9;
        bool matchable;

        //MEMBERFN(int, CheckSpecial, (char special), (special), ADDR_Sexy_Piece_CheckSpecial);
        MEMBERFN(bool, CheckSpecial, (SpecialType special), (special), ADDR_Sexy_Piece_CheckSpecial);
    };

    struct GemTimingInfo
    {
        
    };

    struct WinTwistApp
    {
        int _vftbl;
        char gap4[212];
        __int64 field_D8;
        __int64 field_E0;
        char gapE8[1056];
        char field_508;
        char gap509[172];
        char field_5B5;
        char gap5B6[11];
        char field_5C1;
        char gap5C2[16];
        char field_5D2;
        char gap5D3[13];
        char field_5E0;
        char field_5E1;
        char gap5E2[18];
        char field_5F4;
        char gap5F5[3];
        int field_5F8;
        char gap5FC[4];
        int field_600;
        char gap604[4];
        int field_608;
        char gap60C[332];
        char unknownDemoThing;
        char trialMode;
        char gapNew[14];
        int field_768;
        char gap76C[25];
        char field_785;
        char gap786[94];
        Sexy::GameManager *gameManager;
        int bla1;
        int bla2;
        char field_7F0;
        char field_7F1;
        char gap7F2[10];
        int field_7FC;
        char gap800[24];
        char field_818;
        char gap819[1];
        char field_81A;
        char running;
        char gap81C[24];
        int field_834;
        char gap838[24];
        int field_850;
        char gap854[20];
        int field_868;
        char gap86C[108];
        char field_8D8;
        char field_8D9;
        char field_8DA;
        char gap8DB[17];
        char field_8EC;
        char gap8ED[27];
        int field_908;
        char gap90C[12];
        int field_918;
        char gap91C[12];
        char field_928;
        char gap929[7];
        char field_930;
        char gap931[15];
        int field_940;
        char gap944[4];
        __int64 field_948;
        char gap950[32];
        int field_970;
        char gap974[716];
        char field_C40;
        char field_C41;
        char field_C42;
        char gapC43[5];
        int field_C48;
        char gapC4C[712];
        char field_F14;
        char gapF15[7];
        char field_F1C;
        char gapF1D[11];
        char field_F28;
        char gapF29[7];
        int field_F30;
        char field_F34;
        char field_F35;
        char gapF36[42];
        char field_F60;
        char gapF61[19];
        char field_F74;
        char gapF75[11];
        int field_F80;
        char gapF84[1];
        char field_F85;
        char field_F86;
        char field_F87;
        char gapF88[4];
        char field_F8C;
        char field_F8D;
        char field_F8E;
        char gapF8F[1];
        int field_F90;
        char gapF94[12];
        int field_FA0;
        char gapFA4[128];
        int field_1024;
        char gap1028[32];
        int field_1048;
        char field_104C;
    };

    struct GameManager
    {
        int _vftbl;
        char gap4[12];
        int field_10;
        char gap14New[324];
        int currentLevel;
        char gap14[2040];
        Sexy::WinTwistApp *winTwistApp;
        char newGap4[2520];
        int boardWidth;
        int boardHeight;
        Sexy::Piece **boardPieces;
        char gapNew[244];
        Sexy::Piece *hoverGem;
        char gapNoodles1[320];
        int mPauseCount;
        char gapNew2[60];
        int mouseX;
        int mouseY;
        char gap2372[1600];
        char field_1BF8;
        char gapBanana[7];
        int thingY;
        int thingX;
        char gap1BF9[100];
        char field_1C6C;
        char field_1C6D;
        char field_1C6E;
        char field_1C6F;
        char field_1C70;
        char field_1C71;
        char gap1C72[6];
        char field_1C78;
        char field_1C79;
        char field_1C7A;
        char field_1C7B;
        char gap1C7C[28];
        char iceGemsAllowed;
        char gap1C99[7];
        Sexy::GemTimingInfo mLockGemTimingInfo;
        Sexy::GemTimingInfo skullsProperties;
        Sexy::GemTimingInfo counterProperties;
        Sexy::GemTimingInfo badGemsProperties;
        char gap1E00[88];
        Sexy::GemTimingInfo levelUpProperties;
        Sexy::GemTimingInfo devilGemProperties;
        Sexy::GemTimingInfo coalGemProperties;
        char gap1F60[84];
        char field_1FB4;
        char gap1FB5[387];
        char field_2138;
        char newGap3[199];
        int mSkipMouseClick;
        char newGap2[1224];
        Sexy::Piece *currentPiece;

        MEMBERFN(Sexy::Piece*, GetPiece, (int x, int y), (x, y), ADDR_Sexy_GameManager_GetPiece);
        MEMBERFN(bool, IsSpecial, (Sexy::Piece* piece), (piece), ADDR_Sexy_GameManager_IsSpecial);
        MEMBERFN(void, TwistGems, (bool fromScript, int x, int y), (fromScript, x, y), ADDR_Sexy_GameManager_TwistGems);
        MEMBERFN(void, DoTwistGems, (int x, int y), (x, y), ADDR_Sexy_GameManager_DoTwistGems);
        MEMBERFN(int, GetBoardGemPosX, (int x), (x), ADDR_Sexy_GameManager_GetBoardGemX);
        MEMBERFN(int, GetBoardGemPosY, (int y), (y), ADDR_Sexy_GameManager_GetBoardGemY);
        MEMBERFN(void, SetMousePositionOnBoard, (int x, int y), (x, y), ADDR_Sexy_GameManager_SetMousePositionOnBoard);
        MEMBERFNSIMP(void, ClearBoard, ADDR_Sexy_GameManager_ClearBoard);
        MEMBERFN(int, FillInGems, (bool unknownBool), (unknownBool), ADDR_Sexy_GameManager_FillInGems);

        MEMBERFNSIMP(int, GetBoardPosX, ADDR_Sexy_GameManager_GetBoardXPos);
        MEMBERFNSIMP(int, GetBoardPosY, ADDR_Sexy_GameManager_GetBoardYPos);
    };

    namespace Members
    {
        namespace WinTwistApp
        {
            RAWMEMBERFNSIMP(Sexy::WinTwistApp, bool, Update, ADDR_Sexy_WinTwistApp_Update);
        }

        namespace GameManager
        {
            RAWMEMBERFNSIMP(Sexy::GameManager, void, UpdateBoard, ADDR_Sexy_GameManager_UpdateBoard);
        }
    }

    GLOBALVAR(Sexy::GameManager*, gGameManager, ADDR_Sexy_GameManager_Instance);
    GLOBALVAR(int, gGridWidth, ADDR_Sexy_GridWidth);
    GLOBALVAR(int, gGridHeight, ADDR_Sexy_GridHeight);

}

#endif // __ENGINE_H_