#pragma once
#include <SFML/System/Vector2.hpp>
#include "rng.hpp"
struct PhysicsComponent
{
	sf::Vector2f vel;
	sf::Vector2f pos;
	PhysicsComponent()
	{
		vel.x = getRandom() * 100 + 100;
		vel.y = 0;

		pos.x = getRandom() * 400;
		pos.y = getRandom() * 600;
	}
	static const int mask = 0b10;

};