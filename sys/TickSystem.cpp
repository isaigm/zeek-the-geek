#include "TickSystem.hpp"
namespace ztg
{
    void TickSystem::update(EntityManager &em)
    {
        em.forAllMatching([&](Entity &entity)
        {
            auto &tickCmp = em.getComponent<TickComponent>(entity);
            tickCmp.ticks--;
            if (tickCmp.ticks <= 0)
            {
                em.removeAllComponents(entity);
            }  
        }, m_cmpMaskToCheck, m_tagMask);
    }
}
