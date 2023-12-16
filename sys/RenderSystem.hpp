#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
namespace ztg
{
    struct RenderSystem
    {
        void render(EntityManager &em, sf::RenderTarget &rt);

    private:
        int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
        int m_tagMask = Tags::OBJECT;
    };
}
