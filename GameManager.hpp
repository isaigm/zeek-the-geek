#pragma once
#include "man/EntityManager.hpp"
#include "Level.hpp"
#include "TileSet.hpp"
#include "TilesID.hpp"
struct GameManager
{
	GameManager() : m_tileSet("assets/spritesheet.png", TILE_HEIGHT, TILE_WIDTH)
	{
	}
	void loadLevel(EntityManager &entityManager, int level)
	{
		auto path = getPathLevel(level);
		m_currentLevel.loadFromFile(path);
		auto addEntitiy = [&](int tileID, int x, int y)
		{
			auto &entity = entityManager.createEntity();
			entity.addTag(Tags::OBJECT);
            entity.addTag(Tags::COLLISIONABLE);
			RenderComponent renderComponent;
			m_tileSet.setTile(renderComponent.sprite, m_currentLevel.getTileAt(x, y) - 1); //tiled specific
			PhysicsComponent physicsComponent;
			physicsComponent.pos = {float(x * TILE_WIDTH), float(y * TILE_HEIGHT)};
			entityManager.getComponentStorage().addComponent<RenderComponent>(std::move(renderComponent), entity);
			entityManager.getComponentStorage().addComponent<PhysicsComponent>(std::move(physicsComponent), entity);
			int tag = TilesID::getTag(tileID);
			entity.addTag(tag);
		};
		sf::Vector2i playerPos;
		for (int y = 0; y < m_currentLevel.m_height; y++)
		{
			for (int x = 0; x < m_currentLevel.m_width; x++)
			{
				auto tileID = m_currentLevel.getTileAt(x, y);
				if (TilesID::isEmpty(tileID))
					continue;
				if (TilesID::isPlayer(tileID))
				{
					playerPos = {x, y};
					continue;
				}
				addEntitiy(tileID, x, y);	
			}
		}
		addEntitiy(TilesID::PLAYER, playerPos.x, playerPos.y); //need player at the end because we need to detect collisions for movable objects first, so if they are blocked in the same direction of player, player cant push them 
	}
	static const int TILE_WIDTH   = 36;
	static const int TILE_HEIGHT  = 36;
	static const int LEVEL_WIDTH  = 17;
	static const int LEVEL_HEIGHT = 12;

private:
	std::string getPathLevel(int level)
	{
		return "assets\\level" + std::to_string(level) + ".tmx";
	}
	Level m_currentLevel;
	TileSet m_tileSet;
};