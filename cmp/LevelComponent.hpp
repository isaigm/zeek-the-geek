#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cassert>
struct LevelComponent
{
    static const int EMPTY = -1;
    sf::Vector2i     playerPos;
    std::vector<int> mapIds;
    int              width;
    int              height;
    int              playerId;
    bool             updatePlayerCollisions = false;
    void addId(int id)
    {
        mapIds.push_back(id);
    }
    int getId(int x, int y)
	{
		size_t idx = x + y * width;
        assert(idx < width * height);
		return mapIds[idx];
	}
    int getId(sf::Vector2i pos)
    {
        return getId(pos.x, pos.y);
    }
    void setId(int x, int y, int id)
    {
        size_t idx = x + y * width;
        assert(idx < width * height);
		mapIds[idx] = id;
    }
    void setId(sf::Vector2i pos, int id)
    {
        setId(pos.x, pos.y, id);
    }
};