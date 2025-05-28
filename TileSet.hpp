#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
struct TileSet
{
    TileSet(std::string path, int tileWidth, int tileHeight) : m_tileWidth(tileWidth), m_tileHeight(tileHeight)
    {
        if (!m_texture.loadFromFile(path))
            throw std::runtime_error("Cannot load the file");
        m_width = m_texture.getSize().x;
        m_height = m_texture.getSize().y;
    }
    void setTile( std::shared_ptr<sf::Sprite> &sprite, uint16_t tileId)
    {
        sf::Vector2i tileCount{m_width / m_tileWidth, m_height / m_tileHeight};
        sf::Vector2i tileCoords{tileId % tileCount.x, tileId / tileCount.x};
        sprite->setTexture(m_texture);
        sprite->setTextureRect(getTileRect(tileCoords.x, tileCoords.y));
    }
    const sf::Texture &getTexture()
    {
        return m_texture;
    } 

private:
    sf::IntRect getTileRect(int x, int y)
    {
        sf::IntRect tileRect({x * m_tileWidth, 
        y * m_tileHeight}, {m_tileWidth, m_tileHeight});
        assert(tileRect.position.x < m_width);
        assert(tileRect.position.y < m_height);
        return tileRect;
    }
    sf::Texture m_texture;
    int m_tileWidth, m_tileHeight, m_width, m_height;
};