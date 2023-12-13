#pragma once
#include "../states/ExplodableState.hpp"
struct ExplodableStateComponent
{
    ExplodableState currState = ExplodableState::Disabled;
    float currTimeInState = 0;
    float timeToExplode;
};