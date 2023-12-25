#include "InputSystem.hpp"
namespace ztg
{
    void InputSystem::handleInput(EntityManager &em)
    {
        auto keyPressed    = getKeyPressed();
        auto &level        = em.getSingletonComponent<LevelComponent>();
        auto &playerEntity = em.getEntityById(level.playerId);
        auto &playerData   = em.getComponent<PlayerDataComponent>(playerEntity);
        if (playerData.currState == PlayerState::Dead || playerData.currState == PlayerState::Poisoned)
            return;

        auto &physics = em.getComponent<PhysicsComponent>(playerEntity);
        if (physics.dir != Direction::None)
            return;
        level.updatePlayerCollisions = true;
        switch (keyPressed)
        {
        case DOWN_KEY:
        {
            em.addComponent<AnimationComponent>(ztg::animations[ztg::PLAYER_WALK_DOWN], playerEntity);
            physics.targetPos   = physics.pos;
            physics.targetPos.y += TILE_SIZE;
            physics.dir         = Direction::Down;
        }
        break;
        case UP_KEY:
        {
            em.addComponent<AnimationComponent>(ztg::animations[ztg::PLAYER_WALK_UP], playerEntity);
            physics.targetPos   = physics.pos;
            physics.targetPos.y -= TILE_SIZE;
            physics.dir         = Direction::Up;
        }
        break;
        case RIGHT_KEY:
        {
            em.addComponent<AnimationComponent>(ztg::animations[ztg::PLAYER_WALK_RIGHT], playerEntity);
            physics.targetPos   = physics.pos;
            physics.targetPos.x += TILE_SIZE;
            physics.dir         = Direction::Right;
        }
        break;
        case LEFT_KEY:
        {
            em.addComponent<AnimationComponent>(ztg::animations[ztg::PLAYER_WALK_LEFT], playerEntity);
            physics.targetPos   = physics.pos;
            physics.targetPos.x -= TILE_SIZE;
            physics.dir         = Direction::Left;
        }
        break;
        default:
            level.updatePlayerCollisions = false;
            break;
        }
    }
    sf::Keyboard::Key InputSystem::getKeyPressed()
    {
        std::vector<sf::Keyboard::Key> keys{LEFT_KEY, RIGHT_KEY, DOWN_KEY, UP_KEY};
        for (auto key : keys)
        {
            if (sf::Keyboard::isKeyPressed(key))
                return key;
        }
        return sf::Keyboard::Unknown;
    }
}
