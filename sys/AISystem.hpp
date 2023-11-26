#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
struct AISystem
{
    void update(EntityManager &em, float dt)
    {
        em.forAllMatching([&](Entity &entity)
        {
            auto &physics = em.getComponent<PhysicsComponent>(entity);
            auto &level = em.getSingletonComponent<LevelComponent>();
            int x = physics.pos.x / TILE_WIDTH;
            int y = physics.pos.y / TILE_HEIGHT;
            std::vector<sf::Vector2i> lookAtPositions{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
            for (auto &pos : lookAtPositions)
            {
                if (pos == level.playerPos)
                {
                    updatePlantState(em, entity);
                }
            }
        }, m_cmpMaskToCheck, m_tagMask);
    }

private:
    void updatePlantState(EntityManager &em, Entity &entity)
    {
        auto &level = em.getSingletonComponent<LevelComponent>();
        auto &plantState = em.getComponent<PlantStateComponent>(entity);
        switch (plantState.currState)
        {
        case PlantState::Closed:
            {
                std::vector<sf::Vector2i> frames {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
                plantState.currState = PlantState::Unfolding;
                em.addComponent<AnimationComponent>(AnimationComponent{frames, 0.65f}, entity);
            }
            break;
        case PlantState::Unfolding:
            break;
        case PlantState::Opened:
            break;
        case PlantState::Eating:
            break;
        default:
            break;
        }
    }
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent>();
    int m_tagMask = Tags::PLANT;
};