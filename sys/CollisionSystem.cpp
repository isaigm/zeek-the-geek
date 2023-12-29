#include "CollisionSystem.hpp"
#include "../Animations.hpp"
namespace ztg
{
    void CollisionSystem::update(EntityManager &em)
    {
        auto &gameInfo     = em.getSingletonComponent<GameInfoComponent>();
        if (gameInfo.gameOver) return;
        auto &level        = em.getSingletonComponent<LevelComponent>();
        auto &playerEntity = em.getEntityById(level.playerId);
        auto &playerData   = em.getComponent<PlayerDataComponent>(playerEntity);
        if (!level.updatePlayerCollisions || playerData.currState == PlayerState::Dead)
            return;
        level.updatePlayerCollisions = false;
        auto &physics                = em.getComponent<PhysicsComponent>(playerEntity);
        auto nextPos                 = utils::toWoorldCoords(physics.targetPos);
        if (!level.isInPlayableArea(nextPos))
        {
            physics.dir = Direction::None;
            return;
        }
        if (level.getId(nextPos) == LevelComponent::EMPTY)
        {
            movePlayer(level, nextPos);
            return;
        }
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
    bool CollisionSystem::handlePickableCollisions(EntityManager &em, Entity &playerEntity, Entity &entity)
    {
        auto &playerData  = em.getComponent<PlayerDataComponent>(playerEntity);
        auto &level       = em.getSingletonComponent<LevelComponent>();
        auto &physics     = em.getComponent<PhysicsComponent>(playerEntity);
        auto &gameInfo    = em.getSingletonComponent<GameInfoComponent>();
        auto nextPos      = utils::toWoorldCoords(physics.targetPos);
        bool removePlayer = false;
        if (entity.hasTag(Tags::KEY))
        {
            if (playerData.keyPicked)
            {
                return false;
            }
            playerData.keyPicked = true;
        }
        else if (entity.hasTag(Tags::DOOR))
        {
            if (!playerData.keyPicked)
            {
                return false;
            }
            playerData.keyPicked = false;
        }
        else if (entity.hasTag(Tags::MUSHROOM))
        {
            gameInfo.advanceLevel = true;
        }
        else if (entity.hasTag(Tags::POISONED_MUSHROOM))
        {
            auto &playerData     = em.getComponent<PlayerDataComponent>(playerEntity);
            playerData.currState = PlayerState::Poisoned;
            auto &gameInfo       = em.getSingletonComponent<GameInfoComponent>();
            gameInfo.gameOver    = true;
            removePlayer         = true;
        }
        else if (entity.hasTag(Tags::FLOWER))
        {
            gameInfo.score += 50;
        }
        else if (entity.hasTag(Tags::CHEST))
        {
            gameInfo.score += 100;
        }
        em.getSingletonComponent<SfxComponent>().pick.sound.play();
        utils::prepareEntityToDisappear(em, entity, 10);
        movePlayer(level, nextPos);
        if (removePlayer) level.markPosAsEmpty(nextPos);
        return true;
    }
    bool CollisionSystem::handleMovableCollisions(EntityManager &em, Entity &entity)
    {
        auto &movablePhysics = em.getComponent<PhysicsComponent>(entity);
        auto &level          = em.getSingletonComponent<LevelComponent>();
        auto &playerPhysics  = em.getComponent<PhysicsComponent>(em.getEntityById(level.playerId));
        auto pos             = utils::toWoorldCoords(movablePhysics.pos);
        auto nextPos         = getNextPos(pos, playerPhysics.dir);
        if (!level.isInPlayableArea(nextPos))
        {
            return false;
        }
        if (level.getId(nextPos) != LevelComponent::EMPTY)
        {
            return false;
        }
        if (entity.hasTag(Tags::BOMB))
        {
            utils::activateBomb(em, entity);
        }
        movablePhysics.targetPos = movablePhysics.pos;
        movablePhysics.dir       = playerPhysics.dir;
        int id                   = level.getId(pos);
        movablePhysics.targetPos = utils::moveGivenDirection(playerPhysics.dir, movablePhysics.targetPos, float(TILE_SIZE));
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
        return utils::moveGivenDirection(dir, currPos, 1);
    }
}
