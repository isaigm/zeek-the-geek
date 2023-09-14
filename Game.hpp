#pragma once
#include "man/EntityManager.hpp"
#include "sys/PhysicsSystem.hpp"
#include "sys/RenderSystem.hpp"
#include "sys/InputSystem.hpp"
#include "sys/CollisionSystem.hpp"
#include "GameManager.hpp"
struct Game
{
	Game() : m_entityManager(GameManager::LEVEL_WIDTH * GameManager::LEVEL_HEIGHT),
		m_window(sf::VideoMode(GameManager::LEVEL_WIDTH * GameManager::TILE_WIDTH, 
		GameManager::LEVEL_HEIGHT * GameManager::TILE_HEIGHT), "Zeek the Geek")
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
	void events() {
		sf::Event ev;
		while (m_window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				m_window.close();
				break;
			}else if(ev.type == sf::Event::KeyPressed)
			{
				m_inputSystem.handleInput(m_entityManager, ev.key.code);
			}
		}
	}
	void update(float dt)
	{
		m_collisionSystem.update(m_entityManager);
		m_physicsSystem.update(m_entityManager, dt);

	}
	void render()
	{
		m_window.clear(sf::Color::White);
		m_renderSystem.render(m_entityManager, m_window);
		m_window.display();
	}
	
	sf::RenderWindow m_window;
	EntityManager    m_entityManager;
	GameManager		 m_gameManager;
	PhysicsSystem	 m_physicsSystem;
	RenderSystem	 m_renderSystem;
	InputSystem		 m_inputSystem;
	CollisionSystem  m_collisionSystem;
	
};