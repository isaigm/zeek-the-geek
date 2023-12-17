#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
namespace ztg
{
    struct AnimationSystem
    {
        void update(EntityManager &em, float dt);
    private:
        void animatePlayer(EntityManager &em, Entity &entity, float dt);
        void animateEntity(EntityManager &em, Entity &entity, float dt);
        void setFrame(AnimationComponent &animCmp, RenderComponent &renderCmp);
        int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent, RenderComponent, AnimationComponent>();
        int m_tagMask        = Tags::OBJECT;
    };
}
