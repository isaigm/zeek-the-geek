#pragma once
#include <SFML/Graphics/CircleShape.hpp>
struct RenderComponent
{
	RenderComponent() : shape(5)
	{
		shape.setFillColor(sf::Color::Blue);
	
	}
	sf::CircleShape shape;
	static const int mask = 0b01;
};