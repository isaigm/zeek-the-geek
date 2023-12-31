#pragma once
#include "../states/PlantState.hpp"
#include <SFML/System/Vector2.hpp>
struct PlantDataComponent
{
    PlantState currState   = PlantState::Closed;
    bool       leftAligned = false;
    bool       upAligned   = false;
    sf::Vector2i blockedPos;
};
