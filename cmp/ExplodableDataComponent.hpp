#pragma once
#include "../states/ExplodableState.hpp"
struct ExplodableDataComponent
{
    ExplodableState currState = ExplodableState::Disabled;
    float currTimeInState = 0;
    float timeToExplode;
};