#pragma once
#include "../man/EntityManager.hpp"
struct ResetSystem
{
	void update(EntityManager &em)
	{
		em.forAllMatching([&](auto& e) {
            auto& physics = em.template getComponent<PhysicsComponent>(e);
            if(e.hasTag(Tags::MOVABLE))
            {
                auto& free = em.template getComponent<FreeMovementComponent>(e);
			    for(auto &dir: free.freeDirs) dir = true;
            }
            physics.dir = Direction::None;			

		}, m_cmpMaskToCheck, m_tagMask);
	}
	private:	
		int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent>();
		int m_tagMask = Tags::OBJECT;
};