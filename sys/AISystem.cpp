#include "AISystem.hpp"
#include "../Animations.hpp"
namespace ztg
{
    void AISystem::update(EntityManager &em, float dt)
    {
        em.forAllMatching([&](Entity &entity)
        {
            if (entity.hasTag(Tags::PLANT))
            {
                processPlant(em, entity);
            }else if (entity.hasTag(Tags::CRYSTAL) || entity.hasTag(Tags::BOMB))
            {
                processExplodable(em, entity, dt);
            }
        }, m_cmpMaskToCheck, m_tagMask);
    }


    void AISystem::processExplodable(EntityManager &em, Entity &entity, float dt)
    {
        auto &state   = em.getComponent<ExplodableStateComponent>(entity);
        if (state.currState == ExplodableState::Disabled) return;
        state.currTimeInState += dt;
        auto &physics = em.getComponent<PhysicsComponent>(entity);
        auto &level   = em.getSingletonComponent<LevelComponent>();
        if (state.currTimeInState >= state.timeToExplode)
        {
            state.currState = ExplodableState::Disabled;
            auto pos        = utils::toWoorldCoords(physics.pos);
            if (entity.hasTag(Tags::BOMB))
            {
                processBomb(em, entity);
            }
            level.markPosAsEmpty(pos);
            em.removeAllComponents(entity);
        }      
    }
    void AISystem::processBomb(EntityManager &em, Entity &entity)
    {           
        
        auto &physics = em.getComponent<PhysicsComponent>(entity);
        auto &level   = em.getSingletonComponent<LevelComponent>();
        auto [x, y]   = utils::toWoorldCoords(physics.pos);
        std::vector<sf::Vector2i> lookAtPositions{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        for (auto &pos : lookAtPositions)
        {
            if (!level.isSafe(pos)) continue;
            auto &nearEntity = em.getEntityById(level.getId(pos));
            if (nearEntity.hasTag(Tags::PLAYER))
            {
                auto &playerState     = em.getComponent<PlayerStateComponent>(nearEntity);
                playerState.currState = PlayerState::Dead;
                em.removeComponent<RenderComponent>(nearEntity);
            }
            else if (nearEntity.hasTag(Tags::REMOVABLE))
            {
                level.markPosAsEmpty(pos);
                em.removeAllComponents(nearEntity);
            }
            else if (nearEntity.hasTag(Tags::BOMB))
            {
                utils::activateBomb(em, nearEntity);
            }
        } 
    }
    void AISystem::processPlant(EntityManager &em, Entity &entity)
    {
        auto &physics = em.getComponent<PhysicsComponent>(entity);
        auto &level   = em.getSingletonComponent<LevelComponent>();
        auto [x, y]   = utils::toWoorldCoords(physics.pos);
        std::vector<NearPosition> lookAtPositions{{x - 1, y, Direction::Left}, {x + 1, y, Direction::Right}, {x, y - 1, Direction::Up}, {x, y + 1, Direction::Down}};
        handlePlantTransitions(em, entity);
        for (auto &pos : lookAtPositions)
        {
            if (!level.isSafe({pos.x, pos.y})) continue;
            auto &nearEntity = em.getEntityById(level.getId({pos.x, pos.y}));
            if (nearEntity.hasTag(Tags::PLAYER) || nearEntity.hasTag(Tags::APPLE))
            {
                updatePlantState(em, entity, nearEntity, pos);
            }
        } 
    }
    void AISystem::updatePlantState(EntityManager &em, Entity &plant, Entity &nearEntity, NearPosition pos)
    {
        auto &level        = em.getSingletonComponent<LevelComponent>();
        auto &plantState   = em.getComponent<PlantStateComponent>(plant);
        auto &plantPhysics = em.getComponent<PhysicsComponent>(plant);
        bool isPlayer      = nearEntity.hasTag(Tags::PLAYER);
        bool isApple       = nearEntity.hasTag(Tags::APPLE);
        sf::Vector2f plantPos  = plantPhysics.pos;
        sf::Vector2f entityPos = em.getComponent<PhysicsComponent>(nearEntity).pos;
        plantPos   += {float(TILE_SIZE) / 2.0f, float(TILE_SIZE) / 2.0f};
        entityPos  += {float(TILE_SIZE) / 2.0f, float(TILE_SIZE) / 2.0f};
        auto [x, y] = utils::toWoorldCoords(plantPhysics.pos);

        switch (plantState.currState)
        {
        case PlantState::Closed:
        {
            if (isPlayer)
            {
                plantState.currState = PlantState::Unfolding;
                em.addComponent<AnimationComponent>(ztg::animations[ztg::PLANT_UNFOLDING], plant);
            }
        }
        break;
        case PlantState::Opened:
        {
            float dist = std::abs(utils::getDist(plantPos, entityPos) - TILE_SIZE);
            if (dist < 0.5f)
            {
                if (isPlayer)
                {
                    auto &playerState     = em.getComponent<PlayerStateComponent>(nearEntity);
                    playerState.currState = PlayerState::Dead;
                    plantState.currState  = PlantState::AttackingPlayer;
                    em.addComponent<AnimationComponent>(getAnimationForPlayer(pos.dir), plant);
                }
                else if (isApple)
                {
                    plantState.currState = PlantState::AttackingApple;
                    em.addComponent<AnimationComponent>(getAnimationForApple(pos.dir), plant);
                }
                alignPlant(plantPhysics, plantState, pos.dir);
                em.removeComponent<RenderComponent>(nearEntity);
                em.removeComponent<PhysicsComponent>(nearEntity);
                plantState.blockedPos = {pos.x, pos.y};
                level.setId(pos.x, pos.y, level.getId(x, y));
            }
        }
        break;
        case PlantState::Unfolding:
        case PlantState::AttackingApple:
        case PlantState::AttackingPlayer:
        case PlantState::EatingPlayer:
        case PlantState::EatingApple:
            break;
        default:
            break;
        }
    }

    void AISystem::restorePlantPosition(PhysicsComponent &physics, PlantStateComponent &state)
    {
        if (state.leftAligned)
        {
            physics.pos.x    += TILE_SIZE;
            state.leftAligned = false;
        }
        else if (state.upAligned)
        {
            physics.pos.y  += TILE_SIZE;
            state.upAligned = false;
        }
    }
    void AISystem::handlePlantTransitions(EntityManager &em, Entity &plant)
    {
        if (!plant.hasComponent<AnimationComponent>())
            return;
        auto &animCmp = em.getComponent<AnimationComponent>(plant);
        if (!animCmp.animationFinished)
            return;
        em.removeComponent<AnimationComponent>(plant);
        auto &plantState = em.getComponent<PlantStateComponent>(plant);
        auto &physics    = em.getComponent<PhysicsComponent>(plant);
        auto &currState  = plantState.currState;
        auto &level      = em.getSingletonComponent<LevelComponent>();
        bool mustEat     = false;
        ztg::KindOfAnimation whatAnimation;
        switch (currState)
        {
        case PlantState::Unfolding:
            currState     = PlantState::Opened;
            break;
        case PlantState::EatingApple:
            currState     = PlantState::Closed;
            break;
        case PlantState::AttackingApple:
            currState     = PlantState::EatingApple;
            mustEat       = true;
            whatAnimation = ztg::PLANT_EATING_APPLE;
            break;
        case PlantState::AttackingPlayer:
            currState     = PlantState::EatingPlayer;
            mustEat       = true;
            whatAnimation = ztg::PLANT_EATING_PLAYER;
            break;
        default:
            break;
        }
        if (mustEat)
        {
            em.addComponent<AnimationComponent>(ztg::animations[whatAnimation], plant);
            restorePlantPosition(physics, plantState);
            level.markPosAsEmpty(plantState.blockedPos);
        }
    }
    void AISystem::alignPlant(PhysicsComponent &physics, PlantStateComponent &state, Direction dir)
    {
        if (dir == Direction::Up)
        {
            physics.pos.y  -= TILE_SIZE;
            state.upAligned = true;
        }
        else if (dir == Direction::Left)
        {
            physics.pos.x    -= TILE_SIZE;
            state.leftAligned = true;
        }
    }
    AnimationComponent AISystem::getAnimationForApple(Direction dir)
    {
        assert(dir != Direction::None);
        switch (dir)
        {
        case Direction::Left:
            return ztg::animations[ztg::PLANT_ATTACKING_LEFT_APPLE];
        case Direction::Right:
            return ztg::animations[ztg::PLANT_ATTACKING_RIGHT_APPLE];
        case Direction::Up:
            return ztg::animations[ztg::PLANT_ATTACKING_UP_APPLE];
        case Direction::Down:
            return ztg::animations[ztg::PLANT_ATTACKING_DOWN_APPLE];
        default:
            break;
        }
    }
    AnimationComponent AISystem::getAnimationForPlayer(Direction dir)
    {
        assert(dir != Direction::None);
        switch (dir)
        {
        case Direction::Left:
            return ztg::animations[ztg::PLANT_ATTACKING_LEFT_PLAYER];
        case Direction::Right:
            return ztg::animations[ztg::PLANT_ATTACKING_RIGHT_PLAYER];
        case Direction::Up:
            return ztg::animations[ztg::PLANT_ATTACKING_UP_PLAYER];
        case Direction::Down:
            return ztg::animations[ztg::PLANT_ATTACKING_DOWN_PLAYER];
        default:
            break;
        }
    }
    
}