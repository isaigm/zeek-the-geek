#pragma once
#include <SFML/Graphics/Sprite.hpp>
struct RenderComponent
{
	RenderComponent(){}
	sf::Sprite sprite;
	static const int mask = 0b1;
};