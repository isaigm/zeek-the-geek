#pragma once
#include "../man/EntityManager.hpp"
#include "../GameManager.hpp"
struct CollisionSystem
{
    void update(EntityManager &em, GameManager &gm)
    {
        em.forAllMatching([&](auto &e1){
            auto &e1Phys = em.getComponentStorage().getPhysicsComponent(e1);
            em.forAllMatching([&](auto &e2){
              
                auto &e2Phys = em.getComponentStorage().getPhysicsComponent(e2);
                if(e1.hasTag(Tags::PLAYER) && (e2.hasTag(Tags::WALL) || e2.hasTag(Tags::PLANT)))
                {
                    solveCollision(e1Phys, e2Phys);
                }
            }, m_cmpMaskToCheck, Tags::COLLISIONABLE);
    
        }, m_cmpMaskToCheck, m_tagMask);
    }
private:
    void solveCollision(PhysicsComponent &e1Phys, PhysicsComponent &e2Phys)
    {
        int tileWidth = GameManager::TILE_WIDTH;
        int tileHeight = GameManager::TILE_HEIGHT;
        if((e1Phys.pos.x + e1Phys.vel.x * tileWidth) == e2Phys.pos.x && e1Phys.pos.y == e2Phys.pos.y)
        {
            e1Phys.vel.x = 0;
        }
        else if((e1Phys.pos.y + e1Phys.vel.y * tileHeight) == e2Phys.pos.y && e1Phys.pos.x == e2Phys.pos.x)
        {
            e1Phys.vel.y = 0;
        }        
    }
    int m_cmpMaskToCheck = RenderComponent::mask | PhysicsComponent::mask;
	int m_tagMask = Tags::OBJECT;
};