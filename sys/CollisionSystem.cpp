#include "CollisionSystem.hpp"
#include "../Animations.hpp"
namespace ztg
{
    void CollisionSystem::update(EntityManager &em)
    {
        auto &level        = em.getSingletonComponent<LevelComponent>();
        auto &playerEntity = em.getEntityById(level.playerId);
        auto &playerState  = em.getComponent<PlayerStateComponent>(playerEntity);
        if (!level.updatePlayerCollisions || playerState.currState == PlayerState::Dead)
            return;
        auto &physics = em.getComponent<PhysicsComponent>(playerEntity);
        auto nextPos  = ztg::toWoorldCoords(physics.targetPos);
        if (level.getId(nextPos) == LevelComponent::EMPTY)
        {
            movePlayer(level, nextPos);
        }
        else
        {
            auto &entity = em.getEntityById(level.getId(nextPos));
            bool canMove = false;
            if (entity.hasTag(Tags::PICKABLE))
            {
                canMove |= handlePickableCollisions(em, playerEntity, entity);
            }
            else if (entity.hasTag(Tags::MOVABLE))
            {
                canMove |= handleMovableCollisions(em, entity);
            }
            if (!canMove)
            {
                physics.dir = Direction::None;
            }
        }
        level.updatePlayerCollisions = false;
    }
    bool CollisionSystem::handlePickableCollisions(EntityManager &em, Entity &playerEntity, Entity &entity)
    {
        auto &playerState = em.getComponent<PlayerStateComponent>(playerEntity);
        auto &level       = em.getSingletonComponent<LevelComponent>();
        auto &physics     = em.getComponent<PhysicsComponent>(playerEntity);
        auto &gameInfo    = em.getSingletonComponent<GameInfoComponent>();
        auto nextPos      = ztg::toWoorldCoords(physics.targetPos);

        if (entity.hasTag(Tags::KEY))
        {
            if (playerState.keyPicked)
            {
                return false;
            }
            playerState.keyPicked = true;
        }
        else if (entity.hasTag(Tags::DOOR))
        {
            if (!playerState.keyPicked)
            {
                return false;
            }
            playerState.keyPicked = false;
        }
        else if (entity.hasTag(Tags::MUSHROOM))
        {
            gameInfo.advanceLevel = true;
        }
        else if (entity.hasTag(Tags::FLOWER))
        {
            gameInfo.score += 50;
        }
        else if (entity.hasTag(Tags::CHEST))
        {
            gameInfo.score += 100;
        }
        em.template removeComponent<RenderComponent>(entity);
        em.template removeComponent<PhysicsComponent>(entity);
        movePlayer(level, nextPos);
        return true;
    }
    bool CollisionSystem::handleMovableCollisions(EntityManager &em, Entity &entity)
    {
        auto &movablePhysics = em.getComponent<PhysicsComponent>(entity);
        auto &level          = em.getSingletonComponent<LevelComponent>();
        auto &playerPhysics  = em.getComponent<PhysicsComponent>(em.getEntityById(level.playerId));
        auto pos             = ztg::toWoorldCoords(movablePhysics.pos);
        auto nextPos         = getNextPos(pos, playerPhysics.dir);
        if (level.getId(nextPos) != LevelComponent::EMPTY)
        {
            return false;
        }
        if (entity.hasTag(Tags::BOMB) && !entity.hasComponent<AnimationComponent>())
        {
            auto &state = em.getComponent<ExplodableStateComponent>(entity);
            state.currState = ExplodableState::Actived;
            em.addComponent<AnimationComponent>(ztg::animations[ztg::BOMB_ACTIVED], entity);
        }
        movablePhysics.targetPos = movablePhysics.pos;
        switch (playerPhysics.dir)
        {
        case Direction::Down:
            movablePhysics.targetPos.y += TILE_SIZE;
            break;
        case Direction::Up:
            movablePhysics.targetPos.y -= TILE_SIZE;
            break;
        case Direction::Right:
            movablePhysics.targetPos.x += TILE_SIZE;
            break;
        case Direction::Left:
            movablePhysics.targetPos.x -= TILE_SIZE;
            break;
        default:
            break;
        }
        movablePhysics.dir = playerPhysics.dir;
        int id = level.getId(pos);
        movePlayer(level, pos);
        level.setId(nextPos.x, nextPos.y, id);
        return true;
    }
    void CollisionSystem::movePlayer(LevelComponent &level, sf::Vector2i nextPos)
    {
        level.markPosAsEmpty(level.playerPos);
        level.playerPos = nextPos;
        level.setId(level.playerPos, level.playerId);
    }
    sf::Vector2i CollisionSystem::getNextPos(sf::Vector2i currPos, Direction dir)
    {
        sf::Vector2i nextPos{currPos};
        switch (dir)
        {
        case Direction::Up:
            nextPos.y--;
            break;
        case Direction::Down:
            nextPos.y++;
            break;
        case Direction::Left:
            nextPos.x--;
            break;
        case Direction::Right:
            nextPos.x++;
            break;
        case Direction::None:
            break;
        }
        return nextPos;
    }
}
