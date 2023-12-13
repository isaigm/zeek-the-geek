#pragma once
#include "cmp/AnimationComponent.hpp"
#include <map>
#include <iostream>

namespace ztg
{
    enum KindOfAnimation
    {
        PLAYER_WALK_LEFT,
        PLAYER_WALK_RIGHT,
        PLAYER_WALK_UP,
        PLAYER_WALK_DOWN,
       
        PLAYER_STANDING_LEFT,
        PLAYER_STANDING_RIGHT,
        PLAYER_STANDING_UP,
        PLAYER_STANDING_DOWN,
        
        PLANT_EATING_APPLE,
        PLANT_EATING_PLAYER,
    
        PLANT_ATTACKING_LEFT_APPLE,
        PLANT_ATTACKING_RIGHT_APPLE,
        PLANT_ATTACKING_DOWN_APPLE,
        PLANT_ATTACKING_UP_APPLE,

        PLANT_ATTACKING_LEFT_PLAYER,
        PLANT_ATTACKING_RIGHT_PLAYER,
        PLANT_ATTACKING_DOWN_PLAYER,
        PLANT_ATTACKING_UP_PLAYER,
        
        PLANT_UNFOLDING,
        
        SIZE_ANIMATIONS

    };
    struct AnimationStorage
    {
        AnimationStorage()
        {
            for (int i = 0; i < SIZE_ANIMATIONS; i++)
            {
                auto kind = KindOfAnimation(i);
                m_animations[kind] = getAnimation(kind);
            }
        }
        AnimationComponent operator[](KindOfAnimation kind)
        {
            return m_animations[kind];
        }
    private:
        AnimationComponent getAnimation(KindOfAnimation kind)
        {
            switch (kind)
            {
            case PLAYER_WALK_LEFT:
            {
                std::vector<AnimationComponent::frame> frames{{6, 12}, {6, 13}, {6, 14}};
                return AnimationComponent{frames, 0.1f, true};
            }
            case PLAYER_WALK_RIGHT:
            {
                std::vector<AnimationComponent::frame> frames{{5, 5}, {5, 6}, {5, 7}};
                return AnimationComponent{frames, 0.1f, true};
            }
            case PLAYER_WALK_UP:
            {
                std::vector<AnimationComponent::frame> frames{{5, 11}, {5, 10}, {5, 12}};
                return AnimationComponent{frames, 0.1f, true};
            }
            case PLAYER_WALK_DOWN:
            {
                std::vector<AnimationComponent::frame> frames{{5, 0}, {5, 8}, {5, 9}};
                return AnimationComponent{frames, 0.1f, true};
            }
            case PLAYER_STANDING_LEFT:
            {
                std::vector<AnimationComponent::frame> frames{{6, 12}};
                return AnimationComponent{frames, 0.0f};
            }
            case PLAYER_STANDING_RIGHT:
            {
                std::vector<AnimationComponent::frame> frames{{5, 5}};
                return AnimationComponent{frames, 0.0f};
            }
            case PLAYER_STANDING_UP:
            {
                std::vector<AnimationComponent::frame> frames{{5, 11}};
                return AnimationComponent{frames, 0.0f};
            }
            break;
            case PLAYER_STANDING_DOWN:
            {
                std::vector<AnimationComponent::frame> frames{{5, 0}};
                return AnimationComponent{frames, 0.0f};
            }
            break;
            case PLANT_EATING_APPLE:
            {
                std::vector<AnimationComponent::frame> frames{{2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 0}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_EATING_PLAYER:
            {
                std::vector<AnimationComponent::frame> frames {{.x = 1, .y = 8, .duration = 3.0f}};
                int repeatedFrames = 3;
                for (int i = 0; i < repeatedFrames; i++)
                {
                    frames.push_back({.x = 1, .y = 9,  .duration = 0.25f});
                    frames.push_back({.x = 1, .y = 10, .duration = 0.25f});
                }
                return AnimationComponent{frames, true};
            }
            case PLANT_ATTACKING_LEFT_APPLE:
            {
                std::vector<AnimationComponent::frame> frames{{9, 2, 2 * TILE_SIZE, TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_RIGHT_APPLE:
            {
                std::vector<AnimationComponent::frame> frames{{9, 3, 2 * TILE_SIZE, TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_UP_APPLE:
            {
                std::vector<AnimationComponent::frame> frames{{9, 0, TILE_SIZE, 2 * TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_DOWN_APPLE:
            {
                std::vector<AnimationComponent::frame> frames{{10, 0, TILE_SIZE, 2 * TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_LEFT_PLAYER:
            {
                std::vector<AnimationComponent::frame> frames{{11, 2, 2 * TILE_SIZE, TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_RIGHT_PLAYER:
            {
                std::vector<AnimationComponent::frame> frames{ {11, 3, 2 * TILE_SIZE, TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_UP_PLAYER:
            {
                std::vector<AnimationComponent::frame> frames{{11, 0, TILE_SIZE, 2 * TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_ATTACKING_DOWN_PLAYER:
            {
                std::vector<AnimationComponent::frame> frames{{12, 0, TILE_SIZE, 2 * TILE_SIZE}};
                return AnimationComponent{frames, 1.5f};
            }
            case PLANT_UNFOLDING:
            {
                std::vector<AnimationComponent::frame> frames{{2, 0}, {2, 1}, {2, 2}, {2, 3}};
                return AnimationComponent{frames, 1.0f};
            }
            }
        }
        std::map<KindOfAnimation, AnimationComponent> m_animations;
    };
    static AnimationStorage animations;
}
