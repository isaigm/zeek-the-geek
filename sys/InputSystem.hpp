#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Window/Keyboard.hpp>
struct InputSystem
{
    void handleInput(EntityManager &em)
    {
        auto keyPressed = getKeyPressed();
        auto &level = em.getSingletonComponent<LevelComponent>();
        auto &playerEntity = em.getEntityById(level.playerId);
        auto &playerState = em.getComponent<PlayerStateComponent>(playerEntity);
        if (playerState.currState == PlayerState::Dead)
            return;

        auto &physics = em.getComponent<PhysicsComponent>(playerEntity);
        if (physics.dir != Direction::None)
            return;
        level.updatePlayerCollisions = true;
        switch (keyPressed)
        {
        case DOWN_KEY:
        {
            std::vector<AnimationComponent::frame> frames{{5, 0}, {5, 8}, {5, 9}};
            em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.1f}, playerEntity);
            physics.targetPos = physics.pos;
            physics.targetPos.y += TILE_SIZE;
            physics.dir = Direction::Down;
        }
        break;
        case UP_KEY:
        {
            std::vector<AnimationComponent::frame> frames{{5, 10}, {5, 11}, {5, 12}};
            em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.1f}, playerEntity);
            physics.targetPos = physics.pos;
            physics.targetPos.y -= TILE_SIZE;
            physics.dir = Direction::Up;
        }
        break;
        case RIGHT_KEY:
        {
            std::vector<AnimationComponent::frame> frames{{5, 5}, {5, 6}, {5, 7}};
            em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.1f}, playerEntity);
            physics.targetPos = physics.pos;
            physics.targetPos.x += TILE_SIZE;
            physics.dir = Direction::Right;
        }
        break;
        case LEFT_KEY:
        {
            std::vector<AnimationComponent::frame> frames{{6, 12}, {6, 13}, {6, 14}};
            em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.1f}, playerEntity);
            physics.targetPos = physics.pos;
            physics.targetPos.x -= TILE_SIZE;
            physics.dir = Direction::Left;
        }
        break;
        default:
            level.updatePlayerCollisions = false;
            break;
        }
    }
    sf::Keyboard::Key getKeyPressed()
    {
        std::vector<sf::Keyboard::Key> keys{LEFT_KEY, RIGHT_KEY, DOWN_KEY, UP_KEY};
        for (auto key : keys)
        {
            if (sf::Keyboard::isKeyPressed(key))
                return key;
        }
        return sf::Keyboard::Unknown;
    }

private:
    static const auto UP_KEY = sf::Keyboard::Up;
    static const auto LEFT_KEY = sf::Keyboard::Left;
    static const auto DOWN_KEY = sf::Keyboard::Down;
    static const auto RIGHT_KEY = sf::Keyboard::Right;
};