#include "Animations.hpp"

namespace ztg
{
    AnimationStorage::AnimationStorage()
    {
        init();
    }
    AnimationComponent AnimationStorage::operator[](KindOfAnimation kind)
    {
        return m_animations[kind];
    }
    void AnimationStorage::init()
    {
        std::vector<AnimationComponent::frame> frames;
        frames = {{6, 12}, {6, 13}, {6, 14}};
        m_animations[PLAYER_WALK_LEFT] = AnimationComponent{frames, 0.1f, true};

        frames = {{5, 5}, {5, 6}, {5, 7}};
        m_animations[PLAYER_WALK_RIGHT] = AnimationComponent{frames, 0.1f, true};

        frames = {{5, 11}, {5, 10}, {5, 12}};
        m_animations[PLAYER_WALK_UP] = AnimationComponent{frames, 0.1f, true};

        frames = {{5, 0}, {5, 8}, {5, 9}};
        m_animations[PLAYER_WALK_DOWN] = AnimationComponent{frames, 0.1f, true};

        frames = {{5, 0}};
        m_animations[PLAYER_STANDING_FRAME] = AnimationComponent{frames, 0.0f};

        frames = {{3, 11}};
        m_animations[EFFECT_FRAME] = AnimationComponent{frames, 0.0f};

        frames = {{3, 12}};
        m_animations[EXPLOSION_FRAME] = AnimationComponent{frames, 0.0f};

        frames = {{2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 0}};
        m_animations[PLANT_EATING_APPLE] = AnimationComponent{frames, 2.0f};

        frames = {{.x = 1, .y = 8, .duration = 3.0f}};
        int repeatedFrames = 3;
        for (int i = 0; i < repeatedFrames; i++)
        {
            frames.push_back({.x = 1, .y = 9, .duration = 0.25f});
            frames.push_back({.x = 1, .y = 10, .duration = 0.25f});
        }
        m_animations[PLANT_EATING_PLAYER] = AnimationComponent{frames, true};

        frames = {{9, 2, 2 * TILE_SIZE, TILE_SIZE}};
        m_animations[PLANT_ATTACKING_LEFT_APPLE] = AnimationComponent{frames, 1.5f};

        frames = {{9, 3, 2 * TILE_SIZE, TILE_SIZE}};
        m_animations[PLANT_ATTACKING_RIGHT_APPLE] = AnimationComponent{frames, 1.5f};

        frames = {{9, 0, TILE_SIZE, 2 * TILE_SIZE}};
        m_animations[PLANT_ATTACKING_UP_APPLE] = AnimationComponent{frames, 1.5f};

        frames = {{10, 0, TILE_SIZE, 2 * TILE_SIZE}};
        m_animations[PLANT_ATTACKING_DOWN_APPLE] = AnimationComponent{frames, 1.5f};

        frames = {{11, 2, 2 * TILE_SIZE, TILE_SIZE}};
        m_animations[PLANT_ATTACKING_LEFT_PLAYER] = AnimationComponent{frames, 1.5f};

        frames = {{11, 3, 2 * TILE_SIZE, TILE_SIZE}};
        m_animations[PLANT_ATTACKING_RIGHT_PLAYER] = AnimationComponent{frames, 1.5f};

        frames = {{11, 0, TILE_SIZE, 2 * TILE_SIZE}};
        m_animations[PLANT_ATTACKING_UP_PLAYER] = AnimationComponent{frames, 1.5f};

        frames = {{12, 0, TILE_SIZE, 2 * TILE_SIZE}};
        m_animations[PLANT_ATTACKING_DOWN_PLAYER] = AnimationComponent{frames, 1.5f};

        frames = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
        m_animations[PLANT_UNFOLDING] = AnimationComponent{frames, 1.0f};

        frames = {{1, 6}, {1, 7}};
        m_animations[CRYSTAL_ACTIVED] = AnimationComponent{frames, 0.5f, true};

        frames = {{1, 3}, {1, 4}};
        m_animations[BOMB_ACTIVED] = AnimationComponent{frames, 0.25f, true};

        frames = {{5, 0}, {6, 0}, {5, 0}, {6, 0}, {6, 5}, {6, 0}, {6, 5}, {6, 6}, {6, 3}, {6, 6}, {6, 9}, {6, 6}, {6, 9}};        
        
        for (int i = 0; i < frames.size() - 1; i++)
        {
            auto &frame = frames[i];
            frame.duration = 0.15f;
        }
        frames.back().duration = 1.0f;
        
        m_animations[PLAYER_POISONED] = AnimationComponent{frames};
    }
}
