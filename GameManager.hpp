#pragma once
#include "man/EntityManager.hpp"
#include "Level.hpp"
#include "TileSet.hpp"
#include "TilesID.hpp"
#include "Levels.hpp"
namespace ztg
{
    struct GameManager
    {
        GameManager();
        void loadLevel(EntityManager &em, int level);

    private:
        std::string getPathLevel(int level);
        Level m_currentLevel;
        TileSet m_tileSet;
    };
}
