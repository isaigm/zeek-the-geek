#pragma once
#include <iostream>
#include <vector>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
namespace ztg
{
    struct Level
    {
        Level(std::string path);
        Level() {}
        uint16_t getTileAt(size_t x, size_t y);
        void loadFromFile(std::string path);
        int getWidth();
        int getHeight();

    private:
        int m_width = 0, m_height = 0;
        std::vector<uint16_t> m_tiles;
    };
}
