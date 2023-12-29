#pragma once
#include "man/EntityManager.hpp"
#include "sys/PhysicsSystem.hpp"
#include "sys/RenderSystem.hpp"
#include "sys/InputSystem.hpp"
#include "sys/CollisionSystem.hpp"
#include "sys/AnimationSystem.hpp"
#include "sys/AISystem.hpp"
#include "sys/TickSystem.hpp"
#include "sys/PlayerStepSoundSystem.hpp"
#include "GameManager.hpp"
#include "Hud.hpp"
namespace ztg
{
    struct Game
    {
        Game();
        void run();

    private:
        void events();
        void update(float dt);
        void restart();
        void render();
        bool                  m_shouldDelay = false;
        float                 m_currTimeDelay = 0.0f;
        sf::RenderWindow      m_window;
        sf::Clock             m_bonusTimer;
        sf::RenderTexture     m_renderTexture;
        sf::Sprite            m_sprite;
        Hud                   m_hud;
        EntityManager         m_entityManager;
        GameManager           m_gameManager;
        AISystem              m_AISystem;
        PhysicsSystem         m_physicsSystem;
        RenderSystem          m_renderSystem;
        InputSystem           m_inputSystem;
        AnimationSystem       m_animationSystem;
        TickSystem            m_tickSystem;
        PlayerStepSoundSystem m_playerSoundSystem;
        CollisionSystem       m_collisionSystem;
    };
}
