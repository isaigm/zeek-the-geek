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
    AnimationComponent(std::vector<frame> frames, float timePerFrame, bool loop = false)
    {
        for (auto &f : frames)
        {
            f.duration = timePerFrame;
        }
        this->frames = frames;
        this->loop   = loop;
    }
    AnimationComponent(std::vector<frame> frames, bool loop = false)
    {
        this->frames = frames;
        this->loop   = loop;
    }
    AnimationComponent() {}
    std::vector<frame> frames;
    int                currFrame{};
    float              currTime{};
    bool               loop = false;
    bool               animationFinished = false;

};