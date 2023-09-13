#pragma once
#include <SFML/Window/Keyboard.hpp>
struct InputComponent
{
	static const auto LEFT_KEY   = sf::Keyboard::Left;
	static const auto RIGHT_KEY  = sf::Keyboard::Right;
	static const auto UP_KEY     = sf::Keyboard::Up;
	static const auto DOWN_KEY   = sf::Keyboard::Down;
	static const int  mask 		 = 0b100;
};