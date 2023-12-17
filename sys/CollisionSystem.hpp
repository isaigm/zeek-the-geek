#pragma once
#include "../man/EntityManager.hpp"
#include "../Utility.hpp"
namespace ztg
{
    struct CollisionSystem
    {
        void update(EntityManager &em);

    private:
        bool handlePickableCollisions(EntityManager &em, Entity &playerEntity, Entity &entity);
        bool handleMovableCollisions(EntityManager &em, Entity &entity);
        void movePlayer(LevelComponent &level, sf::Vector2i nextPos);
        sf::Vector2i getNextPos(sf::Vector2i currPos, Direction dir);
        int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent>();
        int m_tagMask = Tags::PLAYER;
    };
}
