#pragma once
#include <array>
struct TilesID
{
	static const int EMPTY   = 0;
	static const int PLAYER  = 6;

	static const int PLANT_1 = 3;
	static const int PLANT_2 = 10;
	static const int PLANT_3 = 17;
	static const int PLANT_4 = 24;

	static const int WALL_1  = 4;
	static const int WALL_2  = 11;
	static const int WALL_3  = 18;
	static const int WALL_4  = 25;
	static const int WALL_5  = 32;
	static const int WALL_6  = 39;
	static const int WALL_7  = 53;
	static const int WALL_8  = 60;
	static const int WALL_9  = 67;

	static bool isEmpty(int id)
	{
		return id == EMPTY;
	}
	static bool isPlayer(int id)
	{
		return id == PLAYER;
	}
	static bool isPlant(int id)
	{
		return std::find(PLANTS.begin(), PLANTS.end(), id) != PLANTS.end();

	}
	static bool isWall(int id)
	{
		return std::find(WALLS.begin(), WALLS.end(), id) != WALLS.end();
	}
	private:
	constexpr static std::array<int, 9> WALLS  {WALL_1, WALL_2, WALL_3, WALL_4, WALL_5, WALL_6, WALL_7, WALL_8, WALL_9};
	constexpr static std::array<int, 4> PLANTS {PLANT_1, PLANT_2, PLANT_3, PLANT_4};
};