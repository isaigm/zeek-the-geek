#pragma once
#include <SFML/System/Vector2.hpp>
enum class Direction
{
	Left,
	Right,
	Up,
	Down,
	None 
};
struct PhysicsComponent
{
	sf::Vector2f pos{};
	sf::Vector2f targetPos {};
	Direction dir = Direction::None;
	float speed = 36.0f;
};