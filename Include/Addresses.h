#ifndef __ADDRESSES_H_
#define __ADDRESSES_H_

// Other
#define BJT_TEXT_START 0x401000
#define BJT_TEXT_SIZE 0x3D6000

#define BJT_IMAGE_BASE BJT_TEXT_START

#define BJT_VERIFY_TEXT 0x7F4304

// Functions
#define ADDR__IsNonwritableInCurrentImage 0x79E170

#define ADDR_Sexy_GameManager_GetPiece 0x6A40C7
#define ADDR_Sexy_GameManager_IsSpecial 0x6A50E8
#define ADDR_Sexy_GameManager_UpdateBoard 0x6D090F
#define ADDR_Sexy_GameManager_TwistGems 0x6C6E56
#define ADDR_Sexy_GameManager_DoTwistGems 0x6BB171
#define ADDR_Sexy_GameManager_GetBoardGemX 0x6A4819
#define ADDR_Sexy_GameManager_GetBoardGemY 0x6A4831
#define ADDR_Sexy_GameManager_SetMousePositionOnBoard 0x6A9D2D
#define ADDR_Sexy_GameManager_ClearBoard 0x6AFE3A
#define ADDR_Sexy_GameManager_FillInGems 0x6C42E3
#define ADDR_Sexy_GameManager_GetBoardXPos 0x6A6AFA
#define ADDR_Sexy_GameManager_GetBoardYPos 0x6A4801
#define ADDR_Sexy_Piece_CheckSpecial 0x728C91
#define ADDR_Sexy_WinTwistApp_Update 0x49D390

// Variables
#define ADDR_Sexy_GameManager_Instance 0x85AEF4
#define ADDR_Sexy_GridWidth 0x84E884
#define ADDR_Sexy_GridHeight 0x84E888

#endif // __ADDRESSES_H_
