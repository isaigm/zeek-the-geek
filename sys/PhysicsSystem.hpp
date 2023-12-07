#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
#include <iostream>
#include <set>
#include <format>
#include <sstream>
#include <cmath>
struct PhysicsSystem
{
    void update(EntityManager &em, float dt)
    {
        em.forAllMatching([&](Entity &e)
        {
            if(e.hasTag(Tags::PLAYER) || e.hasTag(Tags::MOVABLE))
            {
                auto& physics = em.template getComponent<PhysicsComponent>(e);
                if (physics.dir == Direction::None) return;
                switch (physics.dir)
                {
                    case Direction::Down:
                        physics.pos.y += dt * physics.speed;
                        break;
                    case Direction::Up:
                        physics.pos.y -= dt * physics.speed;
                        break;
                    case Direction::Right:
                        physics.pos.x += dt * physics.speed;
                        break;	
                    case Direction::Left:
                        physics.pos.x -= dt * physics.speed;
                        break;			
                    default:
                        break;
                }
                float dist = getDist(physics.pos, physics.targetPos);
                if(dist < 0.7f)
                {
                    physics.dir = Direction::None;
                    physics.pos = physics.targetPos;
                    if(e.hasTag(Tags::CRYSTAL))
                    {
                        int x = physics.pos.x / TILE_SIZE;
                        int y = physics.pos.y / TILE_SIZE;
                        removeCrystals(em, {x, y});
                    }
                }
            } 
        }, m_cmpMaskToCheck, m_tagMask);
    }

private:
    float getDist(sf::Vector2f p, sf::Vector2f q)
    {
        float dx = p.x - q.x;
        float dy = p.y - q.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    void removeCrystals(EntityManager &em, sf::Vector2i startPos)
    {
        std::set<std::string> visited;
        
        markCrystalsToRemove(em, visited, startPos);
        if(visited.size() < 2) return;
        auto &level = em.getSingletonComponent<LevelComponent>();

        for(auto key: visited)
        {
            std::stringstream ss(key);
            char delim;
            sf::Vector2i pos;
            ss >> pos.x;
            ss >> delim;
            ss >> pos.y;
            auto &crystal = em.getEntityById(level.getId(pos));
            level.markPosAsEmpty(pos);
            em.removeComponent<RenderComponent>(crystal);
            em.removeComponent<PhysicsComponent>(crystal);
        }
    }
    void markCrystalsToRemove(EntityManager &em, std::set<std::string> &visited, sf::Vector2i pos){
        std::vector<sf::Vector2i> contiguousPositions{{pos.x - 1, pos.x}, {pos.x + 1, pos.y}, 
        {pos.x, pos.y - 1}, {pos.x, pos.y + 1}};
        visited.insert(getKey(pos));
        auto &level = em.getSingletonComponent<LevelComponent>();
        for(auto nextPos: contiguousPositions)
        {
            if(level.isInPlayableArea(nextPos) && level.getId(nextPos) != LevelComponent::EMPTY)
            {
                auto key = getKey(nextPos);
                auto &entity = em.getEntityById(level.getId(nextPos));
                if(entity.hasTag(Tags::CRYSTAL) && !visited.contains(key))
                {
                    markCrystalsToRemove(em, visited, nextPos);
                }
            }
        }
    }    
    std::string getKey(sf::Vector2i p)
    {
        return std::format("{},{}", p.x, p.y);
    }
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
    int m_tagMask = Tags::OBJECT;
};
