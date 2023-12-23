#pragma once
#include "../man/EntityManager.hpp"
#include "../Utility.hpp"
namespace ztg
{
    struct AISystem
    {
        void update(EntityManager &em, float dt);

    private:
        struct NearPosition
        {
            int x;
            int y;
            Direction dir;
        };
        void processExplodable(EntityManager &em, Entity &entity, float dt);
        void processBomb(EntityManager &em, Entity &entity);
        void processPlant(EntityManager &em, Entity &entity);
        void updatePlantState(EntityManager &em, Entity &plant, Entity &nearEntity, NearPosition pos);
        void handlePlantTransitions(EntityManager &em, Entity &plant);
        void handlePlayerTransitions(EntityManager &em, Entity &player);
        void restorePlantPosition(PhysicsComponent &physics, PlantStateComponent &state);
        void alignPlant(PhysicsComponent &physics, PlantStateComponent &state, Direction dir);
        AnimationComponent getAnimationForApple(Direction dir);
        AnimationComponent getAnimationForPlayer(Direction dir);
        int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
        int m_tagMask = Tags::OBJECT;
    };
}