#pragma once
#include "../man/EntityManager.hpp"
#include "../GameManager.hpp"
struct CollisionSystem
{
    void update(EntityManager &em, GameManager &gm)
    {
        em.forAllMatching([&](auto &e1){
            em.forAllMatching([&](auto &e2){
                playerCollisions(em, e1, e2);
            }, m_cmpMaskToCheck, Tags::COLLISIONABLE);
    
        }, m_cmpMaskToCheck, m_tagMask);
    }
private:
    bool hasContiguousCollisions(PhysicsComponent &e1Phys, PhysicsComponent &e2Phys)
    {
        int tileWidth = GameManager::TILE_WIDTH;
        int tileHeight = GameManager::TILE_HEIGHT;
        bool xcol = (e1Phys.pos.x + e1Phys.vel.x * tileWidth) == e2Phys.pos.x && e1Phys.pos.y == e2Phys.pos.y;
        bool ycol = (e1Phys.pos.y + e1Phys.vel.y * tileHeight) == e2Phys.pos.y && e1Phys.pos.x == e2Phys.pos.x;
        return xcol || ycol;
    }
    void playerCollisions(EntityManager &em, Entity &e1, Entity &e2)
    {
        if(!e1.hasTag(Tags::PLAYER)) return;
        auto &e1Phys = em.getComponentStorage().getComponent<PhysicsComponent>(e1);
        auto &e2Phys = em.getComponentStorage().getComponent<PhysicsComponent>(e2);
        if(hasContiguousCollisions(e1Phys, e2Phys))
        {
            if(e2.hasTag(Tags::WALL) || e2.hasTag(Tags::PLANT))
            {
                e1Phys.vel = {0, 0};
            }else if(e2.hasTag(Tags::MOVABLE))
            {
                e2Phys.vel = e1Phys.vel;
            }else if(e2.hasTag(Tags::PICKABLE))
            {
                em.getComponentStorage().removeComponent<RenderComponent>(e2);
                em.getComponentStorage().removeComponent<PhysicsComponent>(e2);
            }
        }
    }
    int m_cmpMaskToCheck = Entity::ComponentTraits::getMask<RenderComponent>() | Entity::ComponentTraits::getMask<PhysicsComponent>();
	int m_tagMask = Tags::OBJECT;
};