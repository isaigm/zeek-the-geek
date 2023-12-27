#pragma once
#include <array>
#include <algorithm>
#include "states/PlantState.hpp"
#include "Tags.hpp"
struct TilesID
{
    static const int EMPTY = 0;
    static const int PLAYER = 6;
    static const int MONSTER = 1;

    static const int PLANT_1 = 3;
    static const int PLANT_2 = 42;
    static const int PILL    = 148;
    static const int EGG     = 57;
    static const int ROTTEN_APPLE_1 = 2;
    static const int ROTTEN_APPLE_2 = 15;
    static const int WALL_1 = 4;
    static const int WALL_2 = 17;
    static const int WALL_3 = 30;
    static const int WALL_4 = 43;
    static const int WALL_5 = 56;
    static const int WALL_6 = 69;
    static const int WALL_7 = 95;
    static const int WALL_8 = 108;
    static const int WALL_9 = 121;
    static const int WALL_10 = 82;

    static const int FLOWER = 83;
    static const int BLUE_FLOWER = 70;
    static const int MUSHROOM = 122;
    static const int POISONED_MUSHROOM = 135;
    static const int APPLE = 5;
    static const int BALL = 18;
    static const int CHEST = 134;
    static const int CRYSTAL = 67;
    static const int BOMB = 28;
    static const int KEY = 96;
    static const int DOOR = 44;

    static bool isEgg(int id)
    {
        return id == EGG;
    }
    static bool isPill(int id)
    {
        return id == PILL;
    }
    static bool isRottenApple(int id)
    {
        return id == ROTTEN_APPLE_1 || id == ROTTEN_APPLE_2;
    }
    static bool isPoisonedMushroom(int id)
    {
        return id == POISONED_MUSHROOM;
    }
    static bool isDoor(int id)
    {
        return id == DOOR;
    }
    static bool isKey(int id)
    {
        return id == KEY;
    }
    static bool isBomb(int id)
    {
        return id == BOMB;
    }
    static bool isCrystal(int id)
    {
        return id == CRYSTAL;
    }
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

    static PlantState getPlantState(int id)
    {
        if (id == PLANT_1)
            return PlantState::Closed;
        else if (id == PLANT_2)
            return PlantState::Opened;
        throw std::runtime_error("Invalid plant state");
    }
    static bool isWall(int id)
    {
        return std::find(WALLS.begin(), WALLS.end(), id) != WALLS.end();
    }
    static bool isFlower(int id)
    {
        return id == FLOWER || id == BLUE_FLOWER;
    }
    static bool isMushroom(int id)
    {
        return id == MUSHROOM;
    }
    static bool isApple(int id)
    {
        return id == APPLE;
    }
    static bool isBall(int id)
    {
        return id == BALL;
    }
    static bool isMonster(int id)
    {
        return id == MONSTER;
    }
    static int getTag(int id)
    {
        if (isPill(id) || isEgg(id))
            return Tags::ATTACKABLE;
        if (isMonster(id))
            return Tags::MONSTER | Tags::MOVABLE;
        if (isRottenApple(id))
            return Tags::ROTTEN_APPLE | Tags::ATTACKABLE;
        if (isPoisonedMushroom(id))
            return Tags::PICKABLE | Tags::REMOVABLE | Tags::POISONED_MUSHROOM | Tags::ATTACKABLE;
        if (isPlayer(id))
            return Tags::PLAYER | Tags::MOVABLE;
        if (isPlant(id))
            return Tags::PLANT | Tags::ATTACKABLE;
        if (isWall(id))
            return Tags::WALL;
        if (isFlower(id))
            return Tags::PICKABLE | Tags::FLOWER | Tags::REMOVABLE | Tags::ATTACKABLE;
        if (isChest(id))
            return Tags::PICKABLE | Tags::CHEST;
        if (isMushroom(id))
            return Tags::PICKABLE | Tags::MUSHROOM | Tags::REMOVABLE | Tags::ATTACKABLE;
        if (isKey(id))
            return Tags::PICKABLE | Tags::KEY;
        if (isDoor(id))
            return Tags::PICKABLE | Tags::DOOR;
        if (isBall(id))
            return Tags::MOVABLE;
        if (isBomb(id))
            return Tags::MOVABLE | Tags::BOMB;
        if (isCrystal(id))
            return Tags::MOVABLE | Tags::CRYSTAL;
        if (isApple(id))
            return Tags::MOVABLE | Tags::APPLE | Tags::REMOVABLE | Tags::ATTACKABLE;
        return Tags::UNKNOW;
    }
    static int isChest(int id)
    {
        return id == CHEST;
    }

private:
    constexpr static std::array<int, 10> WALLS{WALL_1, WALL_2, WALL_3, WALL_4, WALL_5, WALL_6, WALL_7, WALL_8, WALL_9, WALL_10};
    constexpr static std::array<int, 2> PLANTS{PLANT_1, PLANT_2};
};