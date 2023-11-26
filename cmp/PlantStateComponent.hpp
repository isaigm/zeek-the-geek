#pragma once
#include "../states/PlantState.hpp"
struct PlantStateComponent
{
    PlantState currState = PlantState::Closed;
};
