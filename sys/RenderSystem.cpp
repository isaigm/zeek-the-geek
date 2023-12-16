#include "RenderSystem.hpp"
namespace ztg
{
    void RenderSystem::render(EntityManager &em, sf::RenderTarget &rt)
    {
        em.forAllMatching([&](Entity &e)
        {
			auto& renderCmp = em.template getComponent<RenderComponent>(e);
			auto& phyCmp    = em.template getComponent<PhysicsComponent>(e);
			renderCmp.sprite.setPosition(phyCmp.pos);
			rt.draw(renderCmp.sprite); 
        }, m_cmpMaskToCheck, m_tagMask);
    }
}
