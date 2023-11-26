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

    template <typename T>
    auto &getComponent(Entity &e)
    {
        return m_componentStorage.getComponent<T>(e);
    }


    template <typename T>
    auto &getSingletonComponent()
    {
        return m_componentStorage.getSingletonComponent<T>();
    }

    template <typename T>
    void addComponent(T &&cmp, Entity &e)
    {
        m_componentStorage.addComponent<T>(std::move(cmp), e);
    }
    template <typename T>
    bool removeComponent(Entity &e)
    {
        return m_componentStorage.removeComponent<T>(e);
    }

    void forAll(auto &&function)
    {
        for (auto &e : m_entities)
        {
            function(e);
        }
    }
    void forAllMatching(auto &&function, int cmpMask, int tag)
    {
        for (auto &e : m_entities)
        {
            if ((e.m_tagMask & tag) == tag && (e.m_componentMask & cmpMask) == cmpMask)
            {
                function(e);
            }
        }
    }
    auto &getEntityById(int id)
    {
        return m_entities[id];
    }
    auto &createEntity() { return m_entities.emplace_back(); }

    int getSize()
    {
        return m_entities.size();
    }

private:
    std::vector<Entity> m_entities;

    ComponentStorage m_componentStorage;
};