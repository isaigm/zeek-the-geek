#pragma once
#include "../man/EntityManager.hpp"
#include "../GameManager.hpp"
#include <iostream>
struct PhysicsSystem
{
	void update(auto& em, float dt)
	{		
		em.forAllMatching([&](auto& e) {
			if(e.hasTag(Tags::PLAYER) || e.hasTag(Tags::MOVABLE))
			{
				auto& physics = em.getComponentStorage().getComponent<PhysicsComponent>(e);
				physics.pos.x += physics.vel.x * GameManager::TILE_WIDTH;
				physics.pos.y += physics.vel.y * GameManager::TILE_HEIGHT;
				physics.vel.x = 0;
				physics.vel.y = 0;
			}
			
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
	int m_tagMask = Tags::OBJECT;
};