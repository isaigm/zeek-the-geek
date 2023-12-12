#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "Constants.hpp"
namespace ztg
{
    static sf::Vector2i toWoorldCoords(sf::Vector2f pos)
    {
        return {int(pos.x) / TILE_SIZE, int(pos.y) / TILE_SIZE};
    }
    static sf::Vector2i toWoorldCoords(float x, float y)
    {
        return {int(x) / TILE_SIZE, int(y) / TILE_SIZE};
    }
    static float getDist(sf::Vector2f p, sf::Vector2f q)
    {
        float dx = p.x - q.x;
        float dy = p.y - q.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}
