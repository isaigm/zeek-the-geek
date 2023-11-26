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
        auto &animCmp = em.template getComponent<AnimationComponent>(entity);
        auto &renderCmp = em.template getComponent<RenderComponent>(entity);
        auto &plantState = em.template getComponent<PlantStateComponent>(entity);
        auto &currState = plantState.currState;
        if (currState == PlantState::Closed || currState == PlantState::Opened)
        {
            return;
        }
        animCmp.currTime += dt;
        if (animCmp.currTime >= animCmp.timePerFrame)
        {
            animCmp.currTime = 0;
            animCmp.currFrame++;
            if (animCmp.currFrame >= animCmp.frames.size())
            {
                animCmp.currFrame = animCmp.frames.size() - 1;
                switch (currState)
                {
                case PlantState::Unfolding:
                    currState = PlantState::Opened;
                    break;
                case PlantState::Eating:
                    currState = PlantState::Closed;
                    break;
                default:
                    break;
                }
            }
        }
        setFrame(animCmp, renderCmp);
    }
    void animatePlayer(EntityManager &em, Entity &entity, float dt)
    {
        auto &animCmp = em.template getComponent<AnimationComponent>(entity);
        auto &renderCmp = em.template getComponent<RenderComponent>(entity);
        auto &physisCmp = em.template getComponent<PhysicsComponent>(entity);
        if (physisCmp.dir != Direction::None)
        {
            animCmp.currTime += dt;
            if (animCmp.currTime >= animCmp.timePerFrame)
            {
                animCmp.currTime = 0;
                animCmp.currFrame++;
                if (animCmp.currFrame >= animCmp.frames.size())
                {
                    animCmp.currFrame = 0;
                }
            }
        }
        else animCmp.currFrame = 0;
        setFrame(animCmp, renderCmp);
    }
    void setFrame(AnimationComponent &animCmp, RenderComponent &renderCmp)
    {
        auto tileCoords = animCmp.frames[animCmp.currFrame];
        sf::IntRect rect{tileCoords.x * TILE_WIDTH, tileCoords.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
        renderCmp.sprite.setTextureRect(rect);
    }
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<RenderComponent, AnimationComponent>();
    int m_tagMask = Tags::OBJECT;
};