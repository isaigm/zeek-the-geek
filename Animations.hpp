#pragma once
#include "cmp/AnimationComponent.hpp"
#include <map>
#include <iostream>

namespace ztg
{
    enum KindOfAnimation
    {
        PLAYER_WALK_LEFT,
        PLAYER_WALK_RIGHT,
        PLAYER_WALK_UP,
        PLAYER_WALK_DOWN,

        PLAYER_STANDING_FRAME,
        EFFECT_FRAME,
        EXPLOSION_FRAME,
        ROTTEN_APPLE,
        PLAYER_POISONED,
        PLANT_EATING_APPLE,
        PLANT_EATING_PLAYER,

        PLANT_ATTACKING_LEFT_APPLE,
        PLANT_ATTACKING_RIGHT_APPLE,
        PLANT_ATTACKING_DOWN_APPLE,
        PLANT_ATTACKING_UP_APPLE,

        PLANT_ATTACKING_LEFT_PLAYER,
        PLANT_ATTACKING_RIGHT_PLAYER,
        PLANT_ATTACKING_DOWN_PLAYER,
        PLANT_ATTACKING_UP_PLAYER,

        MONSTER_WALK_LEFT,
        MONSTER_WALK_RIGHT,
        MONSTER_WALK_UP,
        MONSTER_WALK_DOWN,
        CRYSTAL_ACTIVED,
        BOMB_ACTIVED,

        PLANT_UNFOLDING,

    };
    struct AnimationStorage
    {
        AnimationStorage();
        AnimationComponent operator[](KindOfAnimation kind);

    private:
        void init();
        std::map<KindOfAnimation, AnimationComponent> m_animations;
    };
    static AnimationStorage animations;
}
