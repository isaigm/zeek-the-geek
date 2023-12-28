#pragma once
#include "../man/EntityManager.hpp"
namespace ztg
{
    struct PlayerStepSoundSystem
    {
        void update(EntityManager &em, float dt);

    private:
        float m_currTime = 0;
    };
}
