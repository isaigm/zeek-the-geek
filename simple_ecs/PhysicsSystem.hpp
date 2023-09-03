#pragma once
#include "EntityManager.hpp"
#include <iostream>
struct PhysicsSystem
{
	void update(EntityManager& em, float dt)
	{		
		em.forAll([&](auto& e) {
			auto& physics = em.getComponentStorage().getPhysicsComponent(e);
		});
	}
};