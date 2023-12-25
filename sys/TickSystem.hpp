#pragma once
#include "../man/EntityManager.hpp"
#include <iostream>

namespace ztg
{
    struct TickSystem
    {
        void update(EntityManager &em);
    private:
        int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent, TickComponent>();
        int m_tagMask = Tags::OBJECT;
    };
}
