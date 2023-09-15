#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Window/Keyboard.hpp>
struct InputSystem
{
	void handleInput(EntityManager& em, sf::Keyboard::Key keyPressed)
	{
		em.forAllMatching([&](auto& e) {
			auto &physicsCmp = em.getComponentStorage().template getComponent<PhysicsComponent>(e);
			switch (keyPressed)
			{
			case DOWN_KEY:
				physicsCmp.dir = Direction::Down;
				break;
			case UP_KEY:
				physicsCmp.dir = Direction::Up;
				break;
			case RIGHT_KEY:
				physicsCmp.dir = Direction::Right;	
				break;
			case LEFT_KEY:
				physicsCmp.dir = Direction::Left;
				break;
			default:
				physicsCmp.dir = Direction::None;
				break;
			}
		}, m_cmpMaskToCheck, m_tagMask);
	}
	private:
		static const auto LEFT_KEY   = sf::Keyboard::Left;
		static const auto RIGHT_KEY  = sf::Keyboard::Right;
		static const auto UP_KEY     = sf::Keyboard::Up;
		static const auto DOWN_KEY   = sf::Keyboard::Down;
		int m_cmpMaskToCheck		 =  ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
		int m_tagMask 				 = Tags::PLAYER;
};