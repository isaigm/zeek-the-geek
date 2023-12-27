#include "RenderSystem.hpp"
namespace ztg
{
    void RenderSystem::render(EntityManager &em, sf::RenderTarget &rt)
    {
        em.forAllMatching([&](Entity &entity)
        {
			auto& renderCmp = em.getComponent<RenderComponent>(entity);
			auto& phyCmp    = em.getComponent<PhysicsComponent>(entity);
			renderCmp.sprite.setPosition(phyCmp.pos);
			rt.draw(renderCmp.sprite); 
        }, m_cmpMaskToCheck, m_tagMask);
    }
}
