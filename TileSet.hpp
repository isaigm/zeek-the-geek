#pragma once
#include <SFML/Graphics.hpp>
struct TileSet
{
    TileSet(std::string path, int tileWidth, int tileHeight) : m_tileWidth(tileWidth), m_tileHeight(tileHeight)
    {
        if (!m_texture.loadFromFile(path))
            throw std::runtime_error("Cannot load the file");
        m_width = m_texture.getSize().x;
        m_height = m_texture.getSize().y;
    }
    void setTile(sf::Sprite &sprite, uint16_t tileId)
    {
        sf::Vector2i tileCount{m_width / m_tileWidth, m_height / m_tileHeight};
        sf::Vector2i tileCoords{tileId % tileCount.x, tileId / tileCount.x};
        sprite.setTexture(m_texture);
        sprite.setTextureRect(getTileRect(tileCoords.x, tileCoords.y));
    }

private:
    sf::IntRect getTileRect(int x, int y)
    {
        sf::IntRect tileRect;
        tileRect.width = m_tileWidth;
        tileRect.height = m_tileHeight;
        tileRect.left = x * m_tileWidth;
        tileRect.top = y * m_tileHeight;
        assert(tileRect.left < m_width);
        assert(tileRect.top < m_height);
        return tileRect;
    }
    sf::Texture m_texture;
    int m_tileWidth, m_tileHeight, m_width, m_height;
};