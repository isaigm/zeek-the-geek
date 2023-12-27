#pragma once
#include <SFML/System/Vector2.hpp>
#include "Direction.hpp"
struct PhysicsComponent
{
	sf::Vector2f pos{};
	sf::Vector2f targetPos {};
	Direction dir = Direction::None;
	float speed = 50.0f;
};