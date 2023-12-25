#pragma once
#include "../states/PlayerState.hpp"
struct PlayerDataComponent
{
    PlayerState currState = PlayerState::Alive;
    bool keyPicked        = false;  
};