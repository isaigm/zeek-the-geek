#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../Animations.hpp"
namespace ztg
{
    struct InputSystem
    {
        void handleInput(EntityManager &em);
        sf::Keyboard::Key getKeyPressed();

    private:
        static const auto UP_KEY = sf::Keyboard::Up;
        static const auto LEFT_KEY = sf::Keyboard::Left;
        static const auto DOWN_KEY = sf::Keyboard::Down;
        static const auto RIGHT_KEY = sf::Keyboard::Right;
    };
}
