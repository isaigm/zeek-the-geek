#pragma once
#include "EntityManager.hpp"
struct InputSystem
{
	void handleInput(EntityManager& em)
	{
		em.forAllMatching([&](auto& e) {
			
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = RenderComponent::mask | PhysicsComponent::mask | InputComponent::mask;
	int m_tagMask = Tags::PLAYER;
};