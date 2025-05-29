#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <iostream>
struct RenderComponent
{
	RenderComponent(){}
	std::shared_ptr<sf::Sprite> sprite;
};