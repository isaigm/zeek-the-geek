#pragma once
#include <array>
struct FreeMovementComponent
{
    std::array<bool, 4> freeDirs {true, true, true, true};
};