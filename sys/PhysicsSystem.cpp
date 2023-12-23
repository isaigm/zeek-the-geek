#include "PhysicsSystem.hpp"
namespace ztg
{
    void PhysicsSystem::update(EntityManager &em, float dt)
    {
        em.forAllMatching([&](Entity &entity)
        {
            auto& physics = em.getComponent<PhysicsComponent>(entity);
            if (physics.dir == Direction::None) return;
            utils::moveGivenDirection(physics.dir, physics.pos, dt * physics.speed);
            float dist = utils::getDist(physics.pos, physics.targetPos);
            if (dist > 0.7f) return;
            physics.pos = physics.targetPos;
            physics.dir = Direction::None; 
            if (entity.hasTag(Tags::CRYSTAL)) //specific logic ocurrs when the movable entity reachs its target position 
            {
                auto pos = utils::toWoorldCoords(physics.pos);
                removeCrystals(em, pos);
            }
            else if (entity.hasTag(Tags::PLAYER))
            {
                processPlayer(em, entity);
            }
        }, m_cmpMaskToCheck, m_tagMask);
    }
    void PhysicsSystem::processPlayer(EntityManager &em, Entity &entity)
    {
        auto &playerState = em.getComponent<PlayerStateComponent>(entity);
        if (playerState.currState != PlayerState::Poisoned) return;
        em.addComponent<AnimationComponent>(animations[PLAYER_POISONED], entity);
    }

    void PhysicsSystem::removeCrystals(EntityManager &em, sf::Vector2i startPos)
    {
        std::set<std::string> visited;
        markCrystalsToRemove(em, visited, startPos);
        if (visited.size() < 2)
            return;
        auto &level = em.getSingletonComponent<LevelComponent>();
        for (auto key : visited)
        {
            std::stringstream ss(key);
            char delim;
            sf::Vector2i pos;
            ss >> pos.x;
            ss >> delim;
            ss >> pos.y;
            auto &entity        = em.getEntityById(level.getId(pos));
            auto &state         = em.getComponent<ExplodableStateComponent>(entity);
            state.timeToExplode = 4.1f;
            state.currState     = ExplodableState::Actived;
            em.addComponent<AnimationComponent>(ztg::animations[ztg::CRYSTAL_ACTIVED], entity);
        }
    }
    void PhysicsSystem::markCrystalsToRemove(EntityManager &em, std::set<std::string> &visited, sf::Vector2i pos)
    {
        std::vector<sf::Vector2i> contiguousPositions{{pos.x - 1, pos.y}, {pos.x + 1, pos.y}, {pos.x, pos.y - 1}, {pos.x, pos.y + 1}};
        visited.insert(utils::getKey(pos));
        auto &level = em.getSingletonComponent<LevelComponent>();
        for (auto nextPos : contiguousPositions)
        {
            if (level.isSafe(nextPos))
            {
                auto key     = utils::getKey(nextPos);
                auto &entity = em.getEntityById(level.getId(nextPos));
                if (entity.hasTag(Tags::CRYSTAL) && !visited.contains(key))
                {
                    markCrystalsToRemove(em, visited, nextPos);
                }
            }
        }
    }
}
