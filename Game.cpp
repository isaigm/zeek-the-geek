#include "Game.hpp"

namespace ztg
{
    Game::Game() : m_window(sf::VideoMode(2 * LEVEL_WIDTH * TILE_SIZE, 2 * LEVEL_HEIGHT * TILE_SIZE), "Zeek the Geek"),
                   m_entityManager(LEVEL_WIDTH * LEVEL_HEIGHT)
    {
        sf::Image icon;
        icon.loadFromFile("assets/icon.png");
        m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        m_window.setVerticalSyncEnabled(true);
        m_gameManager.loadLevel(m_entityManager, 0);
        m_hud.getBonus().setValue(8000);
        m_hud.getLevel().setValue(1);
        m_gameManager.loadSounds(m_entityManager);
        m_renderTexture.create(2 * LEVEL_WIDTH * TILE_SIZE, 2 * LEVEL_HEIGHT * TILE_SIZE);
        m_sprite.setTexture(m_renderTexture.getTexture());
        m_sprite.scale({2, 2});
    }
    void Game::run()
    {
        sf::Clock clock;
        while (m_window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            events();
            if (m_shouldDelay)
            {
                m_currTimeDelay += dt;
                if (m_currTimeDelay >= 0.7f) m_shouldDelay  = false;
            }
            else 
            {
                update(dt);
            }
            render();
        }
    }

    void Game::events()
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
                    restart();
                }
                else if (ev.key.code == sf::Keyboard::Q)
                {
                    m_window.close();
                }
                else if (ev.key.code == sf::Keyboard::N)
                {
                    auto &gameInfo        = m_entityManager.getSingletonComponent<GameInfoComponent>();
                    gameInfo.currLevel   += 1;
                    gameInfo.bonus        = 8000;
                    restart();
                }
                break;
            default:
                break;
            }
        }
    }
    void Game::update(float dt)
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
            gameInfo.score     += gameInfo.bonus;
            gameInfo.bonus      = 8000;
            m_shouldDelay       = true;
            restart();
        }
        m_AISystem.update(m_entityManager, dt);
        m_collisionSystem.update(m_entityManager);
        m_physicsSystem.update(m_entityManager, dt);
        m_playerSoundSystem.update(m_entityManager, dt);
        m_animationSystem.update(m_entityManager, dt);
        m_tickSystem.update(m_entityManager);
    }
    void Game::restart()
    {
        auto &gameInfo        = m_entityManager.getSingletonComponent<GameInfoComponent>();
        gameInfo.advanceLevel = false;
        gameInfo.gameOver     = false;
        m_currTimeDelay       = 0.0f;
        m_entityManager.clear();
        m_gameManager.loadLevel(m_entityManager, gameInfo.currLevel);
        m_hud.getLevel().setValue(gameInfo.currLevel + 1);
        m_hud.getBonus().setValue(gameInfo.bonus);
    }
    void Game::render()
    {
        m_window.clear(sf::Color::White);
        m_renderTexture.clear(sf::Color::White);
        m_renderSystem.render(m_entityManager, m_renderTexture);
        m_hud.render(m_renderTexture);
        m_renderTexture.display();
        m_window.draw(m_sprite);
        m_window.display();
    }
}
