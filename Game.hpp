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
        m_gameManager.loadLevel(m_entityManager, 0);
        m_hud.getBonus().setValue(8000);
        m_hud.getLevel().setValue(1);
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
            switch (ev.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::R)
                {
                    auto &gameInfo = m_entityManager.getSingletonComponent<GameInfoComponent>();
                    restart();
                }else if (ev.key.code == sf::Keyboard::Q)
                {
                    m_window.close();
                }
                break;
            default:
                break;
            }
        }
    }
    void update(float dt)
    {
        m_inputSystem.handleInput(m_entityManager);
        auto &gameInfo = m_entityManager.getSingletonComponent<GameInfoComponent>();
        if (m_bonusTimer.getElapsedTime().asSeconds() > 1.2f)
        {
            gameInfo.bonus -= 10;
            gameInfo.bonus = std::max(0, gameInfo.bonus);
            m_hud.getBonus().setValue(gameInfo.bonus);
            m_bonusTimer.restart();
        }
        m_hud.getScore().setValue(gameInfo.score);
        if (gameInfo.advanceLevel)
        {
            gameInfo.currLevel += 1;
            gameInfo.score += gameInfo.bonus;
            gameInfo.bonus = 8000;
            restart();
        }
        m_AISystem.update(m_entityManager);
        m_collisionSystem.update(m_entityManager);
        m_physicsSystem.update(m_entityManager, dt);
        m_animationSystem.update(m_entityManager, dt);
    }
    void restart()
    {
        auto &gameInfo = m_entityManager.getSingletonComponent<GameInfoComponent>();
        gameInfo.advanceLevel = false;
        m_entityManager.clear();
        m_gameManager.loadLevel(m_entityManager, gameInfo.currLevel);
        m_hud.getLevel().setValue(gameInfo.currLevel + 1);
        m_hud.getBonus().setValue(gameInfo.bonus);
    }
    void render()
    {
        m_window.clear(sf::Color::White);
        m_renderSystem.render(m_entityManager, m_window);
        m_hud.render(m_window);
        m_window.display();
    }
    sf::RenderWindow m_window;
    sf::Clock m_bonusTimer;
    Hud m_hud;
    EntityManager m_entityManager;
    GameManager m_gameManager;
    AISystem m_AISystem;
    PhysicsSystem m_physicsSystem;
    RenderSystem m_renderSystem;
    InputSystem m_inputSystem;
    AnimationSystem m_animationSystem;
    CollisionSystem m_collisionSystem;
};