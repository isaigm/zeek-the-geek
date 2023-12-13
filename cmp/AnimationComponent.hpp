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
    AnimationComponent(std::vector<frame> _frames, float timePerFrame, bool _loop = false)
    {
        for (auto &f : _frames)
        {
            f.duration = timePerFrame;
        }
        frames = _frames;
        loop = _loop;
    }
    AnimationComponent(std::vector<frame> _frames, bool _loop = false)
    {
        frames = _frames;
        loop = _loop;
    }
    AnimationComponent() {}
    std::vector<frame> frames;
    int                currFrame{};
    float              currTime{};
    bool               loop = false;
    bool               animationFinished = false;

};