#pragma once
#include <array>
struct FreeMovementComponent
{
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    std::array<bool, 4> m_freeDirs {};
};