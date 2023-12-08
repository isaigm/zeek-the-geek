#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "../Constants.hpp"
struct AnimationComponent
{
    struct frame
    {
        int x;
        int y;
        int width  = TILE_SIZE;
        int height = TILE_SIZE;
    };
    std::vector<frame> frames;
    float              timePerFrame {};
    int                currFrame {};
    float              currTime {};
};