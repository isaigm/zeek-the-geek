#include "Level.hpp"
namespace ztg
{
    Level::Level(std::string path)
    {
        loadFromFile(path);
    }
    uint16_t Level::getTileAt(size_t x, size_t y)
    {
        size_t idx = x + y * m_width;
        assert(idx < m_tiles.size());
        return m_tiles[idx];
    }
    void Level::loadFromFile(std::string path)
    {
        tmx::Map map;
        if (!map.load(path))
            throw std::runtime_error("Cannot load the file");
        const auto &layers = map.getLayers();
        const auto &layer  = layers[0];
        const auto &tiles  = layer->getLayerAs<tmx::TileLayer>().getTiles();
        const auto &dim    = map.getTileCount();
        m_width  = dim.x;
        m_height = dim.y;
        if (m_tiles.size() > 0)
            m_tiles.clear();
        for (size_t i = 0; i < tiles.size(); i++)
        {
            m_tiles.push_back(tiles[i].ID);
        }
    }
    int Level::getWidth()
    {
        return m_width;
    }
    int Level::getHeight()
    {
        return m_height;
    }
}
