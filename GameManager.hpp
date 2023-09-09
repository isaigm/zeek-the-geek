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
		for (int y = 0; y < m_currentLevel.m_height; y++)
		{
			for (int x = 0; x < m_currentLevel.m_width; x++)
			{
				auto tileID = m_currentLevel.getTileAt(x, y);
				if (TilesID::isEmpty(tileID))
					continue;
				auto &entity = entityManager.createEntity();
				entity.addTag(Tags::OBJECT);
                entity.addTag(Tags::COLLISIONABLE);
				RenderComponent renderComponent;
				m_tileSet.setTile(renderComponent.sprite, m_currentLevel.getTileAt(x, y) - 1); //tiled specific
				PhysicsComponent physicsComponent;
				physicsComponent.pos = {float(x * TILE_WIDTH), float(y * TILE_HEIGHT)};
				entityManager.getComponentStorage().addRenderComponent(std::move(renderComponent), entity);
				entityManager.getComponentStorage().addPhysicsComponent(std::move(physicsComponent), entity);
				if (TilesID::isPlayer(tileID))
				{
					entityManager.getComponentStorage().addInputComponent(InputComponent{}, entity);
					entity.addTag(Tags::PLAYER);
				}else if(TilesID::isWall(tileID))
                {
                    entity.addTag(Tags::WALL);
                }else if(TilesID::isPlant(tileID))
                {
                    entity.addTag(Tags::PLANT);
                }
			}
		}
	}
	static const int TILE_WIDTH   = 36;
	static const int TILE_HEIGHT  = 36;
	static const int LEVEL_WIDTH  = 17;
	static const int LEVEL_HEIGHT = 12;

private:
	std::string getPathLevel(int level)
	{
		return "assets/level" + std::to_string(level) + ".tmx";
	}
	Level m_currentLevel;
	TileSet m_tileSet;
};