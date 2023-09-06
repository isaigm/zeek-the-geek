#pragma once
#include <SFML/Window/Keyboard.hpp>
struct InputComponent
{
	static const int LEFT_KEY = sf::Keyboard::Left;
	static const int RIGHT_KEY = sf::Keyboard::Right;
	static const int mask = 0b100;
};