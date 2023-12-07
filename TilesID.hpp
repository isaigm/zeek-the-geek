#pragma once
#include <array>
#include "states/PlantState.hpp"
#include "cmp/Tags.hpp"
struct TilesID
{
    static const int EMPTY = 0;
    static const int PLAYER = 6;

    static const int PLANT_1 = 3;
    static const int PLANT_2 = 42;

    static const int WALL_1 = 4;
    static const int WALL_2 = 17;
    static const int WALL_3 = 30;
    static const int WALL_4 = 43;
    static const int WALL_5 = 56;
    static const int WALL_6 = 69;
    static const int WALL_7 = 95;
    static const int WALL_8 = 108;
    static const int WALL_9 = 121;

    static const int FLOWER = 83;
    static const int MUSHROOM = 122;
    static const int APPLE = 5;
    static const int BALL = 18;
    static const int CHEST = 134;
    static const int CRYSTAL = 67;
    static const int BOMB = 28;

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
        return id == FLOWER;
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
    static int getTag(int id)
    {
        if (isPlayer(id))
            return Tags::PLAYER;
        if (isPlant(id))
            return Tags::PLANT;
        if (isWall(id))
            return Tags::WALL;
        if (isFlower(id) || isMushroom(id) || isChest(id))
            return Tags::PICKABLE;
        if (isBall(id) || isBomb(id))
            return Tags::MOVABLE;
        if (isCrystal(id))
            return Tags::MOVABLE | Tags::CRYSTAL;
        if (isApple(id))
            return Tags::MOVABLE | Tags::APPLE;
        return 0;
    }
    static int isChest(int id)
    {
        return id == CHEST;
    }

private:
    constexpr static std::array<int, 9> WALLS{WALL_1, WALL_2, WALL_3, WALL_4, WALL_5, WALL_6, WALL_7, WALL_8, WALL_9};
    constexpr static std::array<int, 4> PLANTS{PLANT_1, PLANT_2};
};