#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
static int EMPTY = -1;
struct LevelComponent
{
    sf::Vector2i     playerPos;
    std::vector<int> mapIds;
    int              width;
    int              height;
    int              playerId;
    bool             updateCollisions = false;
    void addId(int id)
    {
        mapIds.push_back(id);
    }
    int getId(int x, int y)
	{
		size_t idx = x + y * width;
		return mapIds[idx];
	}
    int getId(sf::Vector2i pos)
    {
        return getId(pos.x, pos.y);
    }
    void setId(int x, int y, int id)
    {
        size_t idx = x + y * width;
		mapIds[idx] = id;
    }
};