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
        int width = TILE_SIZE;
        int height = TILE_SIZE;
        float duration{};
    };
    AnimationComponent(std::vector<frame> _frames, float timePerFrame)
    {
        for (auto &f : _frames)
        {
            f.duration = timePerFrame;
        }
        frames = _frames;
    }
    AnimationComponent(std::vector<frame> _frames)
    {
        frames = _frames;
    }
    AnimationComponent() {}
    std::vector<frame> frames;
    int currFrame{};
    float currTime{};
};