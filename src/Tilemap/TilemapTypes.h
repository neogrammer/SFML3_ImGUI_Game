#pragma once
#include <Resources/Cfg.h>

enum class TileType
{
    InvisibleAndEmpty = 0,
    VisibleAndSolid = 1,
    VisibleAndEmpty = 2,
    InvisibleAndSolid = 3
};

enum class  LevelName
{
    Intro,
    Uninitialized
};


struct TMAP
{
    TMAP();
    ~TMAP();
    TMAP(const TMAP& other);
    TMAP& operator=(const TMAP& other);
    TMAP(TMAP&&);
    TMAP& operator=(TMAP&&);

    std::vector<int> level{};
    int cols{ 1 };
    int rows{ 1 };
    int tw{ 50 };
    int th{ 50 };
};

struct TSET
{
    TSET();
    ~TSET();
    TSET(const TSET& other);
    TSET& operator=(const TSET& other);
    TSET(TSET&&);
    TSET& operator=(TSET&&);


    Cfg::Textures texID{ Cfg::Textures::Invariant };

    std::vector<int> tileDataType{};
    int cols{ 1 };
    int rows{ 1 };
    int tw{ 50 };
    int th{ 50 };
};
//
//struct TMAP
//{
//    TMAP();
//    ~TMAP();
//    TMAP(const TMAP& other);
//    TMAP& operator=(const TMAP& other);
//    TMAP(TMAP&&);
//    TMAP& operator=(TMAP&&);
//
//    std::vector<int> level{};
//    int cols{ 1 };
//    int rows{ 1 };
//    int tw{ 50 };
//    int th{ 50 };
//};
//
//struct TSET
//{
//    TSET();
//    ~TSET();
//    TSET(const TSET& other);
//    TSET& operator=(const TSET& other);
//    TSET(TSET&&);
//    TSET& operator=(TSET&&);
//
//
//    Cfg::Textures texID{ Cfg::Textures::Invariant };
//
//    std::vector<int> tileDataType{};
//    int cols{ 1 };
//    int rows{ 1 };
//    int tw{ 50 };
//    int th{ 50 };
//};


extern TMAP NEWgetLevelData(LevelName level);
extern TSET NEWgetTilesetData(LevelName level);
//
//extern TMAP getLevelData(LevelName level);
//extern TSET getTilesetData(LevelName level);