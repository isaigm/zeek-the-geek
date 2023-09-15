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
	PhysicsComponent(){}
	Direction dir = Direction::None;
};