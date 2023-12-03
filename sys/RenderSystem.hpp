#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
struct RenderSystem
{
    void render(EntityManager &em, sf::RenderTarget &rt)
    {
        em.forAllMatching([&](Entity &e)
        {
			auto& renderCmp = em.template getComponent<RenderComponent>(e);
			auto& phyCmp = em.template getComponent<PhysicsComponent>(e);
			renderCmp.sprite.setPosition(phyCmp.pos);
			rt.draw(renderCmp.sprite);
        }, m_cmpMaskToCheck, m_tagMask);
    }

private:
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
    int m_tagMask = Tags::OBJECT;
};