#pragma once
#include "../man/EntityManager.hpp"
#include "../Utility.hpp"
struct AISystem
{
    void update(EntityManager &em)
    {
        em.forAllMatching([&](Entity &entity)
        {
            auto &physics = em.getComponent<PhysicsComponent>(entity);
            auto &level   = em.getSingletonComponent<LevelComponent>();
            auto [x, y]   = ztg::toWoorldCoords(physics.pos);
            
            std::vector<NearPosition> lookAtPositions{{x - 1, y, Direction::Left}, {x + 1, y, Direction::Right}, 
            {x, y - 1, Direction::Up}, {x, y + 1, Direction::Down}};
            for (auto &pos : lookAtPositions)
            {
                if (!level.isSafe({pos.x, pos.y})) continue;
                auto &nearEntity = em.getEntityById(level.getId({pos.x, pos.y}));
                if (nearEntity.hasTag(Tags::PLAYER) || nearEntity.hasTag(Tags::APPLE))
                {
                    updatePlantState(em, entity, nearEntity, pos);
                }
            } 
        }, m_cmpMaskToCheck, m_tagMask);
    }

private:
    struct NearPosition
    {
        int x;
        int y;
        Direction dir;
    };
    void updatePlantState(EntityManager &em, Entity &plant, Entity &nearEntity, NearPosition pos)
    {
        auto &level        = em.getSingletonComponent<LevelComponent>();
        auto &plantState   = em.getComponent<PlantStateComponent>(plant);
        auto &plantPhysics = em.getComponent<PhysicsComponent>(plant);
        bool isPlayer      = nearEntity.hasTag(Tags::PLAYER);
        bool isApple       = nearEntity.hasTag(Tags::APPLE);
        sf::Vector2f plantPos  = plantPhysics.pos;
        sf::Vector2f entityPos = em.getComponent<PhysicsComponent>(nearEntity).pos;
        plantPos  += {float(TILE_SIZE) / 2.0f, float(TILE_SIZE) / 2.0f};
        entityPos += {float(TILE_SIZE) / 2.0f, float(TILE_SIZE) / 2.0f};
        auto [x, y] = ztg::toWoorldCoords(plantPhysics.pos);

        switch (plantState.currState)
        {
        case PlantState::Closed:
        {
            if (isPlayer)
            {
                std::vector<AnimationComponent::frame> frames{{2, 0}, {2, 1}, {2, 2}, {2, 3}};
                plantState.currState = PlantState::Unfolding;
                em.addComponent<AnimationComponent>(AnimationComponent{frames, 1.0f}, plant);
            }
        }
        break;
        case PlantState::Unfolding:
            break;
        case PlantState::Opened:
        {
            float dist = std::abs(ztg::getDist(plantPos, entityPos) - TILE_SIZE);
            if (dist < 0.5f)
            {
                std::vector<AnimationComponent::frame> frames;
                if (isPlayer)
                {
                    auto &playerState = em.getComponent<PlayerStateComponent>(nearEntity);
                    playerState.currState = PlayerState::Dead;
                    frames = getFramesForPlayer(pos.dir);
                    plantState.currState = PlantState::EatingPlayer;
                    em.addComponent<AnimationComponent>(AnimationComponent{frames}, plant);
                }
                else if (isApple)
                {
                    frames = getFramesForApple(pos.dir);
                    plantState.currState = PlantState::EatingApple;
                    em.addComponent<AnimationComponent>(AnimationComponent{frames, 1.5f}, plant);
                }
                alignPlant(plantPhysics, plantState, pos.dir);
                em.removeComponent<RenderComponent>(nearEntity);
                em.removeComponent<PhysicsComponent>(nearEntity);
                plantState.blockedPos = {pos.x, pos.y};
                level.setId(pos.x, pos.y, level.getId(x, y));
            }
        }
        break;
        case PlantState::EatingPlayer:
        case PlantState::EatingApple:
            break;
        default:
            break;
        }
    }
    void alignPlant(PhysicsComponent &physics, PlantStateComponent &state, Direction dir)
    {
        if (dir == Direction::Up)
        {
            physics.pos.y -= TILE_SIZE;
            state.upAligned = true;
        }
        else if (dir == Direction::Left)
        {
            physics.pos.x -= TILE_SIZE;
            state.leftAligned = true;
        }
    }
    std::vector<AnimationComponent::frame> getFramesForApple(Direction dir)
    {
        assert(dir != Direction::None);
        std::vector<AnimationComponent::frame> frames{{}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 0}};
        switch (dir)
        {
        case Direction::Left:
            frames[0] = {9, 2, 2 * TILE_SIZE, TILE_SIZE};
            return frames;
        case Direction::Right:
            frames[0] = {9, 3, 2 * TILE_SIZE, TILE_SIZE};
            return frames;
        case Direction::Up:
            frames[0] = {9, 0, TILE_SIZE, 2 * TILE_SIZE};
            return frames;
        case Direction::Down:
            frames[0] = {10, 0, TILE_SIZE, 2 * TILE_SIZE};
            return frames;
        default:
            break;
        }
    }
    std::vector<AnimationComponent::frame> getFramesForPlayer(Direction dir)
    {
        assert(dir != Direction::None);
        std::vector<AnimationComponent::frame> frames{{}, {.x = 1, .y = 8, .duration = 3.0f}};
        int repeatedFrames = 3;
        for (int i = 0; i < repeatedFrames; i++)
        {
            frames.push_back({.x = 1, .y = 9,  .duration = 0.25f});
            frames.push_back({.x = 1, .y = 10, .duration = 0.25f});
        }
        switch (dir)
        {
        case Direction::Left:
            frames[0] = {11, 2, 2 * TILE_SIZE, TILE_SIZE, 1.5f};
            return frames;
        case Direction::Right:
            frames[0] = {11, 3, 2 * TILE_SIZE, TILE_SIZE, 1.5f};
            return frames;
        case Direction::Up:
            frames[0] = {11, 0, TILE_SIZE, 2 * TILE_SIZE, 1.5f};
            return frames;
        case Direction::Down:
            frames[0] = {12, 0, TILE_SIZE, 2 * TILE_SIZE, 1.5f};
            return frames;
        default:
            break;
        }
    }
    int m_cmpMaskToCheck = ComponentTraits::getCmpMask<PhysicsComponent>();
    int m_tagMask = Tags::PLANT;
};