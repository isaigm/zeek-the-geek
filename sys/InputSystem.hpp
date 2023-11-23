#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Window/Keyboard.hpp>
struct InputSystem
{
	void handleInput(EntityManager &em, sf::Keyboard::Key keyPressed)
	{
		auto &level = em.getSingletonComponent<LevelComponent>();
		auto &playerEntity = em.getEntityById(level.playerId);
		auto &physics = em.template getComponent<PhysicsComponent>(playerEntity);
		if (physics.dir != Direction::None)
			return;
		level.updateCollisions = true;
		switch (keyPressed)
		{
		case DOWN_KEY:
		{
			std::vector<sf::Vector2i> frames{{5, 0}, {5, 8}, {5, 9}};
			em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.2f}, playerEntity);
			physics.targetPos = physics.pos;
			physics.targetPos.y += TILE_HEIGHT;
			physics.dir = Direction::Down;
		}
		break;
		case UP_KEY:
		{
			std::vector<sf::Vector2i> frames{{5, 10}, {5, 11}, {5, 12}};
			em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.2f}, playerEntity);
			physics.targetPos = physics.pos;
			physics.targetPos.y -= TILE_HEIGHT;
			physics.dir = Direction::Up;
		}
		break;
		case RIGHT_KEY:
		{
			std::vector<sf::Vector2i> frames{{5, 5}, {5, 6}, {5, 7}};
			em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.2f}, playerEntity);
			physics.targetPos = physics.pos;
			physics.targetPos.x += TILE_WIDTH;
			physics.dir = Direction::Right;
		}
		break;
		case LEFT_KEY:
		{
			std::vector<sf::Vector2i> frames{{6, 12}, {6, 13}, {6, 14}};
			em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.2f}, playerEntity);
			physics.targetPos = physics.pos;
			physics.targetPos.x -= TILE_WIDTH;
			physics.dir = Direction::Left;
		}
		break;
		default:
			level.updateCollisions = false;
			break;
		}
	}

private:
	
	static const auto UP_KEY = sf::Keyboard::Up;
	static const auto LEFT_KEY = sf::Keyboard::Left;
	static const auto DOWN_KEY = sf::Keyboard::Down;
	static const auto RIGHT_KEY = sf::Keyboard::Right;
};