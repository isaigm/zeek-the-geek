#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
struct CollisionSystem
{
    void update(EntityManager &em)
    {
        auto &level = em.getSingletonComponent<LevelComponent>();
        em.forAllMatching([&](Entity &entity)
        {
            auto &physics = em.getComponent<PhysicsComponent>(entity);
            auto &render = em.getComponent<RenderComponent>(entity);

            auto &level = em.getSingletonComponent<LevelComponent>();
            render.sprite.setColor(sf::Color::Red);
            int x = physics.pos.x / TILE_WIDTH;
            int y = physics.pos.y / TILE_HEIGHT;
        }, m_cmpMaskToCheck, m_tagMask);
        
        if (!level.updateCollisions)
            return;
        auto &playerEntity = em.getEntityById(level.playerId);
        auto &physics = em.getComponent<PhysicsComponent>(playerEntity);
        auto nextPos = getNextPos(level.playerPos, physics.dir);
        if (level.getId(nextPos) == EMPTY)
        {
            movePlayer(level, nextPos);
        }
        else
        {
            auto &entity = em.getEntityById(level.getId(nextPos));
            if (entity.hasTag(Tags::PICKABLE))
            {
                em.template removeComponent<RenderComponent>(entity);
                em.template removeComponent<PhysicsComponent>(entity);
                movePlayer(level, nextPos);
            }
            else if (entity.hasTag(Tags::MOVABLE))
            {
                handleMovableCollisions(em, entity);
            }
            else
            {
                physics.dir = Direction::None;
            }
        }
        level.updateCollisions = false;
    }

private:
    void handleMovableCollisions(EntityManager &em, Entity &entity)
    {
        auto &physics = em.getComponent<PhysicsComponent>(entity);
        auto &level = em.getSingletonComponent<LevelComponent>();
        auto &playerPhysics = em.getComponent<PhysicsComponent>(em.getEntityById(level.playerId));
        int x = physics.pos.x / TILE_WIDTH;
        int y = physics.pos.y / TILE_HEIGHT;
        auto nextPos = getNextPos({x, y}, playerPhysics.dir);
        if (level.getId(nextPos) == EMPTY)
        {
            physics.targetPos = physics.pos;
            switch (playerPhysics.dir)
            {
            case Direction::Down:
                physics.targetPos.y += TILE_HEIGHT;
                break;
            case Direction::Up:
                physics.targetPos.y -= TILE_HEIGHT;
                break;
            case Direction::Right:
                physics.targetPos.x += TILE_WIDTH;
                break;
            case Direction::Left:
                physics.targetPos.x -= TILE_WIDTH;
                break;
            default:
                break;
            }
            physics.dir = playerPhysics.dir;
            int id = level.getId(x, y);
            movePlayer(level, {x, y});
            level.setId(nextPos.x, nextPos.y, id);
        }else
        {
            playerPhysics.dir = Direction::None;
        }
    }
    void movePlayer(LevelComponent &level, sf::Vector2i nextPos)
    {
        level.setId(level.playerPos.x, level.playerPos.y, EMPTY);
        level.playerPos = nextPos;
        level.setId(level.playerPos.x, level.playerPos.y, level.playerId);
    }
    sf::Vector2i getNextPos(sf::Vector2i currPos, Direction dir)
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
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent>();
    int m_tagMask = Tags::PLANT;
};