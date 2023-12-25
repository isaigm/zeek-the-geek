#pragma once
#include "man/EntityManager.hpp"
#include "Level.hpp"
#include "TileSet.hpp"
#include "TilesID.hpp"
namespace ztg
{
    struct GameManager
    {
        GameManager();
        void loadLevel(EntityManager &em, int level);
        void loadSounds(EntityManager &em);

    private:
        void loadSfx(SfxComponent::Sfx &sfx, std::string path);
        std::string getPathLevel(int level);
        Level m_currentLevel;
        TileSet m_tileSet;
    };
}
