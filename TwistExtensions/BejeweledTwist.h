#pragma once

#include <Engine.h>
#include <string>

class BejeweledTwist
{
public:
    BejeweledTwist();
    ~BejeweledTwist();

    static Sexy::Piece::Skin GetSkinByName(std::string name);
    static Sexy::Piece::SpecialType GetSpecialByName(std::string name);

    std::string GetPieceSkinName(Sexy::Piece::Skin skin) const;
    std::string GetPieceSpecialName(Sexy::Piece::SpecialType special) const;
    Sexy::Piece::Skin GetRandomSkin() const;
    void TwistGemsAt(bool fromScript, int x, int y) const;
    void GetHoverPos(int& x, int& y) const;
    void SetPieceSkin(int x, int y, Sexy::Piece::Skin skin) const;
    Sexy::Piece::Skin GetPieceSkin(int x, int y) const;
    void SetPieceSkinAtHover(Sexy::Piece::Skin skin) const;
    void SetPieceSpecial(int x, int y, Sexy::Piece::SpecialType special) const;
    void SetPieceSpecialAtHover(Sexy::Piece::SpecialType special) const;
    void ClearBoard() const;
    void FillBoard() const;
    bool CheckSpecial(int x, int y, Sexy::Piece::SpecialType special) const;
    Sexy::Piece::SpecialType GetSpecial(int x, int y) const;
    void SetCounter(int x, int y, int counter) const;
    int GetCounter(int x, int y) const;
    void SetPieceType(int x, int y, int type) const;
    int GetPieceType(int x, int y) const;
    void SetOldSkin(int x, int y, Sexy::Piece::Skin skin) const;
    Sexy::Piece::Skin GetOldSkin(int x, int y) const;
    void SetPieceMatchable(int x, int y, bool matchable) const;
    bool GetPieceMatchable(int x, int y) const;

    Sexy::Piece* GetPiece(int x, int y) const;

    bool hasGameManager() const;
    Sexy::GameManager* getGameManager() const;
};

extern BejeweledTwist* gBejeweledTwist;