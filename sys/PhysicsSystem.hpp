#pragma once
#include "../man/EntityManager.hpp"
#include "../Utility.hpp"
#include "../Animations.hpp"
#include <iostream>
#include <set>
#include <sstream>
namespace ztg
{
    struct PhysicsSystem
    {
        void update(EntityManager &em, float dt);
    private:
        void activateCrystals(EntityManager &em, sf::Vector2i startPos);
        void markCrystalsToActivate(EntityManager &em, std::set<std::string> &visited, sf::Vector2i pos);
        void processPlayer(EntityManager &em, Entity &entity);
        int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
        int m_tagMask = Tags::MOVABLE;
    };
}
