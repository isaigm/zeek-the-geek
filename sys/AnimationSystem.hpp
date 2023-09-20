#pragma once
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
#include <SFML/Window/Keyboard.hpp>
struct AnimationSystem
{
	void update(EntityManager& em, float dt)
	{
		em.forAllMatching([&](Entity &e) {
			auto &animCmp = em.template getComponent<AnimationComponent>(e);
            auto &renderCmp = em.template getComponent<RenderComponent>(e);
            auto &physisCmp = em.template getComponent<PhysicsComponent>(e);
            if(physisCmp.dir != Direction::None)
            {
                animCmp.currTime += dt;
                if(animCmp.currTime >= animCmp.timePerFrame)
                {
                    animCmp.currTime = 0;
                    animCmp.currFrame++;
                    if(animCmp.currFrame >= animCmp.frames.size())
                    {
                        animCmp.currFrame = 0;
                    }
                }
            }else animCmp.currFrame = 0;
            auto tileCoords = animCmp.frames[animCmp.currFrame];
            sf::IntRect rect { tileCoords.x * TILE_WIDTH, tileCoords.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
            renderCmp.sprite.setTextureRect(rect);

		}, m_cmpMaskToCheck, m_tagMask);
	}
	private:
		int m_cmpMaskToCheck		 = ComponentTraits::getCmpMask<RenderComponent, AnimationComponent>();
		int m_tagMask 				 = Tags::PLAYER;
};