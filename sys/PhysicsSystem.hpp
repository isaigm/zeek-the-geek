#pragma once
#include "../man/EntityManager.hpp"
#include "../GameManager.hpp"
#include <iostream>
struct PhysicsSystem
{
	void update(EntityManager& em, float dt)
	{		
		em.forAllMatching([&](auto& e) {
			auto& physics = em.getComponentStorage().getPhysicsComponent(e);
			physics.pos.x += physics.vel.x * GameManager::TILE_WIDTH;
            physics.pos.y += physics.vel.y * GameManager::TILE_HEIGHT;
            physics.vel.x = 0;
			physics.vel.y = 0;
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = RenderComponent::mask | PhysicsComponent::mask;
	int m_tagMask = Tags::PLAYER;
};