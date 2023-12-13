#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "../man/EntityManager.hpp"
#include "../Constants.hpp"
struct AnimationSystem
{
    void update(EntityManager &em, float dt)
    {
        em.forAllMatching([&](Entity &e)
        {
            if(e.hasTag(Tags::PLAYER))
            {
                animatePlayer(em, e, dt);
            }else if(e.hasTag(Tags::PLANT))
            {
                animatePlant(em, e, dt);
            } 
        }, m_cmpMaskToCheck, m_tagMask);
    }

private:
    void animatePlant(EntityManager &em, Entity &entity, float dt)
    {
        auto &plantState = em.getComponent<PlantStateComponent>(entity);   
        auto &currState  = plantState.currState;
        if (currState == PlantState::Closed || currState == PlantState::Opened)
        {
            return;
        }
        animateEntity(em, entity, dt);
    }
    void animatePlayer(EntityManager &em, Entity &entity, float dt)
    {
        auto &physics = em.getComponent<PhysicsComponent>(entity);
        auto &animCmp = em.getComponent<AnimationComponent>(entity);
        if (physics.dir == Direction::None)
        {
            animCmp.loop      = false;
            animCmp.currFrame = 0;
            animCmp.currTime  = 0;
        }
        animateEntity(em, entity, dt);
    }
    void animateEntity(EntityManager &em, Entity &entity, float dt)
    {
        auto &animCmp   = em.getComponent<AnimationComponent>(entity);
        if (animCmp.animationFinished) return;
        auto &renderCmp = em.getComponent<RenderComponent>(entity);
        animCmp.currTime += dt;
        float currFrameDuration = animCmp.frames[animCmp.currFrame].duration;
        if (animCmp.currTime  >= currFrameDuration)
        {
            animCmp.currTime = 0;
            animCmp.currFrame++;
            if (animCmp.currFrame >= animCmp.frames.size())
            {
                if (animCmp.loop)
                {
                    animCmp.currFrame = 0;
                }else 
                {
                    animCmp.currFrame = animCmp.frames.size() - 1;
                    animCmp.animationFinished = true;
                }
            }
        }
        setFrame(animCmp, renderCmp);
    }
    void setFrame(AnimationComponent &animCmp, RenderComponent &renderCmp)
    {
        auto frame = animCmp.frames[animCmp.currFrame];
        sf::IntRect rect {frame.x * TILE_SIZE, frame.y * TILE_SIZE, frame.width, frame.height};
        renderCmp.sprite.setTextureRect(rect);
    }
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent, RenderComponent, AnimationComponent>();
    int m_tagMask = Tags::OBJECT;
};