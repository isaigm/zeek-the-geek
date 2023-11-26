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
	void loadLevel(EntityManager &em, int level)
	{
		auto path = getPathLevel(level);
		m_currentLevel.loadFromFile(path);
		auto addEntitiy = [&](int tileID, int x, int y)
		{
			auto &entity = em.createEntity();
			entity.addTag(Tags::OBJECT);
			entity.addTag(Tags::COLLISIONABLE);
			RenderComponent renderComponent;
			m_tileSet.setTile(renderComponent.sprite, m_currentLevel.getTileAt(x, y) - 1); // tiled specific
			PhysicsComponent physicsComponent;
			physicsComponent.pos = {float(x * TILE_WIDTH), float(y * TILE_HEIGHT)};
			em.addComponent<RenderComponent>(std::move(renderComponent), entity);
			em.addComponent<PhysicsComponent>(std::move(physicsComponent), entity);
			int tag = TilesID::getTag(tileID);
			switch (tag)
			{
			case Tags::PLANT:
			{
				PlantStateComponent state;
				state.currState = TilesID::getPlantState(tileID);
				em.addComponent<PlantStateComponent>(std::move(state), entity);
			}
			break;
			default:
				break;
			}
			entity.addTag(tag);
		};
		bool playerFound = false;
		sf::Vector2i playerPos;
		em.getSingletonComponent<LevelComponent>().width = m_currentLevel.getWidth();
		em.getSingletonComponent<LevelComponent>().height = m_currentLevel.getHeight();

		for (int y = 0; y < m_currentLevel.getHeight(); y++)
		{
			for (int x = 0; x < m_currentLevel.getWidth(); x++)
			{
				auto tileID = m_currentLevel.getTileAt(x, y);
				if (TilesID::isEmpty(tileID))
				{
					em.getSingletonComponent<LevelComponent>().addId(LevelComponent::EMPTY);
					continue;
				}
				else if (TilesID::isPlayer(tileID))
				{
					playerFound = true;
					playerPos = {x, y};
					em.getSingletonComponent<LevelComponent>().playerPos = playerPos;
					em.getSingletonComponent<LevelComponent>().playerId = em.getSize();
				}
				em.getSingletonComponent<LevelComponent>().addId(em.getSize());
				addEntitiy(tileID, x, y);
			}
		}
		if (!playerFound)
			throw std::runtime_error("cannot find the player");
	}

private:
	std::string getPathLevel(int level)
	{
		return "assets/level" + std::to_string(level) + ".tmx";
	}
	Level m_currentLevel;
	TileSet m_tileSet;
};