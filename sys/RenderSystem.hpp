#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
struct RenderSystem
{
	void render(auto &em, sf::RenderTarget &rt)
	{
		em.forAllMatching([&](auto& e) {
			auto& renderCmp = em.getComponentStorage().template getComponent<RenderComponent>(e);
			auto& phyCmp = em.getComponentStorage().template getComponent<PhysicsComponent>(e);
			renderCmp.sprite.setPosition(phyCmp.pos);
			rt.draw(renderCmp.sprite);
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, PhysicsComponent>();
	int m_tagMask = Tags::OBJECT;
};