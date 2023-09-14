#pragma once
#include <SFML/System/Vector2.hpp>
struct PhysicsComponent
{
	sf::Vector2i vel{};
	sf::Vector2f pos{};
	PhysicsComponent(){}
};