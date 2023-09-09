#pragma once
#include "../man/EntityManager.hpp"
struct InputSystem
{
	void handleInput(EntityManager& em, sf::Keyboard::Key keyPressed)
	{
		em.forAllMatching([&](auto& e) {
			auto &inputCmp = em.getComponentStorage().getInputComponent(e);
			auto &physicsCmp = em.getComponentStorage().getPhysicsComponent(e);
			if(keyPressed == inputCmp.DOWN_KEY)
			{
				physicsCmp.vel.x = 0;
				physicsCmp.vel.y = 1;
			}else if(keyPressed == inputCmp.UP_KEY)
			{
				physicsCmp.vel.x = 0;
				physicsCmp.vel.y = -1;
			}else if(keyPressed == inputCmp.RIGHT_KEY)
			{
				physicsCmp.vel.y = 0;
				physicsCmp.vel.x = 1;	
			}else if(keyPressed == inputCmp.LEFT_KEY)
			{
				physicsCmp.vel.y = 0;
				physicsCmp.vel.x = -1;
			}
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = RenderComponent::mask | PhysicsComponent::mask | InputComponent::mask;
	int m_tagMask = Tags::PLAYER;
};