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
struct Game
{
    Game() : m_window(sf::VideoMode(LEVEL_WIDTH * TILE_SIZE, LEVEL_HEIGHT * TILE_SIZE), "Zeek the Geek"),
             m_entityManager(LEVEL_WIDTH * LEVEL_HEIGHT)
    {
        m_window.setVerticalSyncEnabled(true);
        m_gameManager.loadLevel(m_entityManager, 1);
    }
    void run()
    {
        sf::Clock clock;
        while (m_window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            events();
            update(dt);
            render();
        }
    }

private:
    void events()
    {
        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                m_window.close();
                break;
            }
            else if (ev.type == sf::Event::KeyPressed)
            {
                m_inputSystem.handleInput(m_entityManager, ev.key.code);
            }
        }
    }
    void update(float dt)
    {
        m_AISystem.update(m_entityManager, dt);
        m_collisionSystem.update(m_entityManager);
        m_physicsSystem.update(m_entityManager, dt);
        m_animationSystem.update(m_entityManager, dt);
    }
    void render()
    {
        m_window.clear(sf::Color::White);
        m_renderSystem.render(m_entityManager, m_window);
        m_hud.render(m_window);
        m_window.display();
    }

    sf::RenderWindow m_window;
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