#pragma once
#include "../man/EntityManager.hpp"
struct InputSystem
{
	void handleInput(EntityManager& em, sf::Keyboard::Key keyPressed)
	{
		em.forAllMatching([&](auto& e) {
			auto &inputCmp = em.getComponentStorage().getComponent<InputComponent>(e);
			auto &physicsCmp = em.getComponentStorage().getComponent<PhysicsComponent>(e);
			switch (keyPressed)
			{
			case inputCmp.DOWN_KEY:
				physicsCmp.vel.x = 0;
				physicsCmp.vel.y = 1;
				break;
			case inputCmp.UP_KEY:
				physicsCmp.vel.x = 0;
				physicsCmp.vel.y = -1;
				break;
			case inputCmp.RIGHT_KEY:
				physicsCmp.vel.y = 0;
				physicsCmp.vel.x = 1;	
				break;
			case inputCmp.LEFT_KEY:
				physicsCmp.vel.y = 0;
				physicsCmp.vel.x = -1;
				break;
			default:
				break;
			}
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = Entity::ComponentTraits::getMask<RenderComponent>() | Entity::ComponentTraits::getMask<PhysicsComponent>() | Entity::ComponentTraits::getMask<InputComponent>();
	int m_tagMask = Tags::PLAYER;
};