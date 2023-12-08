#pragma once
#include "../states/PlayerState.hpp"
struct PlayerStateComponent
{
    PlayerState currState = PlayerState::Alive;
    bool keyPicked        = false;  
};