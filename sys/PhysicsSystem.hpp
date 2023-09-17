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
				auto& physics = em.template getComponent<PhysicsComponent>(e);
				switch (physics.dir)
				{
				case Direction::Down:
					physics.pos.y += GameManager::TILE_HEIGHT;
					break;
				case Direction::Up:
					physics.pos.y -= GameManager::TILE_HEIGHT;
					break;
				case Direction::Right:
					physics.pos.x += GameManager::TILE_WIDTH;
					break;	
				case Direction::Left:
					physics.pos.x -= GameManager::TILE_WIDTH;
					break;	
				case Direction::None:
					break;		
				default:
					break;
				}
			}
		}, m_cmpMaskToCheck, m_tagMask);
	}
	private:
		int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
		int m_tagMask = Tags::OBJECT;
};
