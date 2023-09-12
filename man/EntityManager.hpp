#pragma once
#include <vector>
#include "../cmp/Tags.hpp"
#include "ComponentStorage.hpp"

struct EntityManager
{
   
    EntityManager(int numEntities = 1)
    {
        m_entities.reserve(numEntities);
    }
    ComponentStorage &getComponentStorage()
    {
        return m_componentStorage;
    }
    void removeComponents(Entity& e)
    {
      
    }
    void removeEntity(Entity& e)
    {
        removeComponents(e);
        auto it = std::remove_if(m_entities.begin(), m_entities.end(), [e](Entity &ent) {
            return e == ent;
        });
        m_entities.erase(it, m_entities.end());
    }
    void forAll(auto &&function) {
        for (auto& e : m_entities) {
            function(e);
        }
    }
    void forAllMatching(auto &&function, int cmpMask, int tag)
    {
        for (auto& e : m_entities)
        {
            if ((e.m_tagMask & tag) == tag && (e.m_componentMask & cmpMask) == cmpMask)
            {
                function(e);
            }
        }
    }
    auto& createEntity() { return m_entities.emplace_back(); }
    std::vector<Entity>& getEntityVector() { return m_entities; }
private:
    std::vector<Entity> m_entities;
    
    ComponentStorage m_componentStorage;
};