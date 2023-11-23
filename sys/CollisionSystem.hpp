#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
struct CollisionSystem
{
    void update(EntityManager &em)
    {
        auto &level = em.getSingletonComponent<LevelComponent>();
        if (!level.updateCollisions)
            return;
        auto &playerEntity = em.getEntityById(level.playerId);
        auto &physics = em.template getComponent<PhysicsComponent>(playerEntity);
        auto nextPos = getNextPos(level, physics.dir);
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
            else
            {
                physics.dir = Direction::None;
            }
        }
        level.updateCollisions = false;
    }

private:
    void movePlayer(LevelComponent &level, sf::Vector2i nextPos)
    {
        level.setId(level.playerPos.x, level.playerPos.y, EMPTY);
        level.playerPos = nextPos;
        level.setId(level.playerPos.x, level.playerPos.y, level.playerId);
    }
    sf::Vector2i getNextPos(LevelComponent &level, Direction dir)
    {
        sf::Vector2i nextPos{level.playerPos};
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
    int m_tagMask = Tags::OBJECT;
};