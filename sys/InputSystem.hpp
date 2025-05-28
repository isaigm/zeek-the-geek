#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "../Animations.hpp"
#include "../man/EntityManager.hpp"
namespace ztg
{
    struct InputSystem
    {
        void handleInput(EntityManager &em);
        sf::Keyboard::Key getKeyPressed();

    private:
        static const auto UP_KEY    = sf::Keyboard::Key::Up;
        static const auto LEFT_KEY  = sf::Keyboard::Key::Left;
        static const auto DOWN_KEY  = sf::Keyboard::Key::Down;
        static const auto RIGHT_KEY = sf::Keyboard::Key::Right;
    };
}
