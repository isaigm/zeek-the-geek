#pragma once
#include "man/EntityManager.hpp"
#include "sys/PhysicsSystem.hpp"
#include "sys/RenderSystem.hpp"
#include "sys/InputSystem.hpp"
#include "sys/CollisionSystem.hpp"
#include "sys/AnimationSystem.hpp"
#include "sys/AISystem.hpp"
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
        sf::RenderWindow m_window;
        sf::Clock        m_bonusTimer;
        Hud              m_hud;
        EntityManager    m_entityManager;
        GameManager      m_gameManager;
        AISystem         m_AISystem;
        PhysicsSystem    m_physicsSystem;
        RenderSystem     m_renderSystem;
        InputSystem      m_inputSystem;
        AnimationSystem  m_animationSystem;
        CollisionSystem  m_collisionSystem;
    };
}
