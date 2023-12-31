#pragma once
#include <vector>
#include "../Tags.hpp"
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
        assert(size_t(id) < m_entities.size());
        return m_entities[id];
    }
    auto &createEntity() { return m_entities.emplace_back(); }

    int getSize()
    {
        return m_entities.size();
    }
    void removeAllComponents(Entity &e)
    {
        removeComponent<RenderComponent>(e);
        removeComponent<PhysicsComponent>(e);
        removeComponent<AnimationComponent>(e);
        removeComponent<TickComponent>(e);
        removeComponent<PlantDataComponent>(e);
        removeComponent<MonsterDataComponent>(e);
        removeComponent<PlayerDataComponent>(e);
        removeComponent<ExplodableDataComponent>(e);
    }
    void clear()
    {
        for (auto &e : m_entities)
        {
            removeAllComponents(e);
        }
        m_entities.clear();
    }

private:
    std::vector<Entity> m_entities;
    ComponentStorage m_componentStorage;
};