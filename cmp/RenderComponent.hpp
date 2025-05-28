#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
struct RenderComponent
{
	//RenderComponent(const sf::Texture &texture) : sprite(std::make_shared<sf::Sprite>(texture)) {}
	RenderComponent(){}
	std::shared_ptr<sf::Sprite> sprite;

};