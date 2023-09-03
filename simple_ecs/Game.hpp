#pragma once
#include "EntityManager.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "SlotMap.hpp"
#include "Level.hpp"
#include "TileSet.hpp"

struct Game
{
	Game() : m_entityManager(LEVEL_WIDTH * LEVEL_HEIGHT),
		m_window(sf::VideoMode(LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT), "Zeek the Geek"), 
		m_currentLevel("assets/level1.tmx"), 
		m_tileSet("assets/spritesheet.png", TILE_WIDTH, TILE_HEIGHT)
	{
		m_window.setVerticalSyncEnabled(true);

		for (int y = 0; y < m_currentLevel.m_height; y++)
		{
			for (int x = 0; x < m_currentLevel.m_width; x++)
			{
				if (m_currentLevel.getTileAt(x, y) == 0) continue;
				auto& entity = m_entityManager.createEntity();
				entity.addTag(Tags::OBJECT);
				RenderComponent renderComponent;
				m_tileSet.setTile(renderComponent.sprite, m_currentLevel.getTileAt(x, y) - 1);
				PhysicsComponent physicsComponent;
				physicsComponent.pos = { float(x * TILE_WIDTH), float(y * TILE_HEIGHT) };
				m_entityManager.getComponentStorage().addRenderComponent(std::move(renderComponent), entity);
				m_entityManager.getComponentStorage().addPhysicsComponent(std::move(physicsComponent), entity);
			}
		}
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
			}
		}
	}
	void update(float dt)
	{
		m_physicsSystem.update(m_entityManager, dt);
	}
	void render()
	{
		m_window.clear(sf::Color::White);
		m_renderSystem.render(m_entityManager, m_window);
		m_window.display();
	}
	sf::RenderWindow m_window;
	EntityManager	 m_entityManager;
	PhysicsSystem	 m_physicsSystem;
	RenderSystem	 m_renderSystem;
	Level			 m_currentLevel;
	TileSet			 m_tileSet;
	static const int TILE_WIDTH   = 36;
	static const int TILE_HEIGHT  = 36;
	static const int LEVEL_WIDTH  = 17;
	static const int LEVEL_HEIGHT = 12;
};