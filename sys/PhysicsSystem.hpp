#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
#include <iostream>
#include <cmath>
struct PhysicsSystem
{
	void update(auto& em, float dt)
	{		
		em.forAllMatching([&](Entity &e) {
			if(e.hasTag(Tags::PLAYER) || e.hasTag(Tags::MOVABLE))
			{
				auto& physics = em.template getComponent<PhysicsComponent>(e);
				if (physics.dir == Direction::None) return;
				switch (physics.dir)
				{
					case Direction::Down:
						physics.pos.y += dt * physics.speed;
						break;
					case Direction::Up:
						physics.pos.y -= dt * physics.speed;
						break;
					case Direction::Right:
						physics.pos.x += dt * physics.speed;
						break;	
					case Direction::Left:
						physics.pos.x -= dt * physics.speed;
						break;			
					default:
						break;
				}
				float dist = getDist(physics.pos, physics.targetPos);
				if(dist < 0.7f)
				{
					physics.dir = Direction::None;
					physics.pos = physics.targetPos;
				}
			}
		}, m_cmpMaskToCheck, m_tagMask);
	}
	private:
		float getDist(sf::Vector2f p, sf::Vector2f q)
		{
			float dx = p.x - q.x;
			float dy = p.y - q.y;
			return std::sqrt(dx * dx + dy * dy);
		}
		int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
		int m_tagMask = Tags::OBJECT;
};
