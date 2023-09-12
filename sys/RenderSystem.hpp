#pragma once
#include "../man/EntityManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
struct RenderSystem
{
	void render(EntityManager &em, sf::RenderTarget &rt)
	{
		em.forAllMatching([&](auto& e) {
			auto& renderCmp = em.getComponentStorage().getComponent<RenderComponent>(e);
			auto& phyCmp = em.getComponentStorage().getComponent<PhysicsComponent>(e);
			renderCmp.sprite.setPosition(phyCmp.pos);
			rt.draw(renderCmp.sprite);
		}, m_cmpMaskToCheck, m_tagMask);
	}
	int m_cmpMaskToCheck = Entity::ComponentTraits::getMask<RenderComponent>() | Entity::ComponentTraits::getMask<PhysicsComponent>();
	int m_tagMask = Tags::OBJECT;
};