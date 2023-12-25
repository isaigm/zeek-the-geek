#include "AnimationSystem.hpp"
namespace ztg
{
    void AnimationSystem::update(EntityManager &em, float dt)
    {
        em.forAllMatching([&](Entity &e)
        {
            if (e.hasTag(Tags::PLAYER))
            {
                animatePlayer(em, e, dt);
            }
            else
            {
                animateEntity(em, e, dt);
            } 
        }, m_cmpMaskToCheck, m_tagMask);
    }
    void AnimationSystem::animatePlayer(EntityManager &em, Entity &entity, float dt)
    {
        auto &physics = em.getComponent<PhysicsComponent>(entity);
        auto &animCmp = em.getComponent<AnimationComponent>(entity);
        auto &data    = em.getComponent<PlayerDataComponent>(entity);
        if (physics.dir == Direction::None && data.currState == PlayerState::Alive) 
        {
            animCmp.loop      = false;
            animCmp.currFrame = 0;
            animCmp.currTime  = 0;
        }
        animateEntity(em, entity, dt);
    }
    void AnimationSystem::animateEntity(EntityManager &em, Entity &entity, float dt)
    {
        auto &animCmp = em.getComponent<AnimationComponent>(entity);
        if (animCmp.animationFinished)
            return;
        auto &renderCmp  = em.getComponent<RenderComponent>(entity);
        animCmp.currTime += dt;
        float currFrameDuration = animCmp.frames[animCmp.currFrame].duration;
        if (animCmp.currTime >= currFrameDuration)
        {
            animCmp.currTime = 0;
            animCmp.currFrame++;
            if (animCmp.currFrame >= animCmp.frames.size())
            {
                if (animCmp.loop)
                {
                    animCmp.currFrame = 0;
                }
                else
                {
                    animCmp.currFrame = animCmp.frames.size() - 1;
                    animCmp.animationFinished = true;
                }
            }
        }
        setFrame(animCmp, renderCmp);
    }
    void AnimationSystem::setFrame(AnimationComponent &animCmp, RenderComponent &renderCmp)
    {
        auto frame = animCmp.frames[animCmp.currFrame];
        sf::IntRect rect{frame.x * TILE_SIZE, frame.y * TILE_SIZE, frame.width, frame.height};
        renderCmp.sprite.setTextureRect(rect);
    }
}
