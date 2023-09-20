#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
struct CollisionSystem
{
    void update(EntityManager &em)
    {
        em.forAllMatching([&](auto &e1){
            em.forAllMatching([&](auto &e2){ 
                movableCollisions(em, e1, e2);
                playerCollisions(em, e1, e2);     
            },m_cmpMaskToCheck, Tags::COLLISIONABLE);
        }, m_cmpMaskToCheck, m_tagMask);
    }

private:
    bool hasContiguousCollisions(PhysicsComponent &e1Phys, PhysicsComponent &e2Phys)
    {
        return isSomethingAt(e1Phys.pos, e2Phys.pos, e1Phys.dir);
    }
    bool isSomethingAt(sf::Vector2f pos, sf::Vector2f nextPos, Direction dir)
    {
        switch (dir)
        {
        case Direction::Up:
            return (pos.y - TILE_HEIGHT) == nextPos.y && pos.x == nextPos.x;
        case Direction::Down:
            return (pos.y + TILE_HEIGHT) == nextPos.y && pos.x == nextPos.x;
        case Direction::Left:
            return (pos.x - TILE_WIDTH) == nextPos.x && pos.y == nextPos.y;
        case Direction::Right:
            return (pos.x + TILE_WIDTH) == nextPos.x && pos.y == nextPos.y;
        case Direction::None:
            return pos == nextPos;
        }
        return false;
    }
    void playerCollisions(EntityManager &em, Entity &e1, Entity &e2)
    {
        if (!e1.hasTag(Tags::PLAYER))
            return;
        auto &e1Phys = em.template getComponent<PhysicsComponent>(e1);
        auto &e2Phys = em.template getComponent<PhysicsComponent>(e2);
        if (hasContiguousCollisions(e1Phys, e2Phys))
        {
            resolvePlayerCollisions(em, e1, e2);
        }
    }
    void resolvePlayerCollisions(EntityManager &em, Entity &e1, Entity &e2)
    {
        auto &e1Phys = em.getComponent<PhysicsComponent>(e1);
        auto &e2Phys = em.getComponent<PhysicsComponent>(e2);
        if (e2.hasTag(Tags::WALL) || e2.hasTag(Tags::PLANT))
        {
            e1Phys.dir = Direction::None;
        }
        else if (e2.hasTag(Tags::MOVABLE))
        {
            auto &free = em.template getComponent<FreeMovementComponent>(e2);
            if (!free.freeDirs[int(e1Phys.dir)])
            {
                e1Phys.dir = Direction::None;
            }else if(e2Phys.dir == Direction::None)
            {
                e2Phys.targetPos = e2Phys.pos;
                switch (e1Phys.dir)
				{
					case Direction::Down:
                        e2Phys.targetPos.y += TILE_HEIGHT;
						break;
					case Direction::Up:
                        e2Phys.targetPos.y -= TILE_HEIGHT;
						break;
					case Direction::Right:
                        e2Phys.targetPos.x += TILE_WIDTH;
						break;	
					case Direction::Left:
                        e2Phys.targetPos.x -= TILE_WIDTH;
						break;			
					default:
						break;
				}
            }
            e2Phys.dir = e1Phys.dir;
        }
        else if (e2.hasTag(Tags::PICKABLE))
        {
            em.template removeComponent<RenderComponent>(e2);
            em.template removeComponent<PhysicsComponent>(e2);
        }
    }
    void movableCollisions(EntityManager &em, Entity &e1, Entity &e2)
    {
        if (!e1.hasTag(Tags::MOVABLE))
            return;
        auto &e1Phys = em.template getComponent<PhysicsComponent>(e1);
        auto &e2Phys = em.template getComponent<PhysicsComponent>(e2);
        auto &e1Free = em.template getComponent<FreeMovementComponent>(e1);
        std::array<Direction, 4> possibleDirections { Direction::Up, Direction::Down, Direction::Left, Direction::Right};
        for (auto &dir : possibleDirections)
        {
            if (isSomethingAt(e1Phys.pos, e2Phys.pos, dir))
            {
                e1Free.freeDirs[int(dir)] = false;
            }
        }
    }
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent>();
    int m_tagMask = Tags::OBJECT;
};