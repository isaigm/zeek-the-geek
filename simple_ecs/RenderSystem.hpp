#pragma once
#include "EntityManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
struct RenderSystem
{
	void render(EntityManager &em, sf::RenderTarget &rt)
	{
		em.forAllMatching([&](auto& e) {
			auto& renderCmp = em.getComponentStorage().getRenderComponent(e);
			auto& phyCmp = em.getComponentStorage().getPhysicsComponent(e);
			renderCmp.shape.setPosition(phyCmp.pos);
			rt.draw(renderCmp.shape);
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = RenderComponent::mask | PhysicsComponent::mask;
	int m_tagMask = Tags::particle;
};