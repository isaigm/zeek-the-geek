#include "PlayerStepSoundSystem.hpp"
namespace ztg
{
    void PlayerStepSoundSystem::update(EntityManager &em, float dt)
    {
        auto &level         = em.getSingletonComponent<LevelComponent>();
        auto &player        = em.getEntityById(level.playerId);
        auto &playerData    = em.getComponent<PlayerDataComponent>(player);
        auto &playerPhysics = em.getComponent<PhysicsComponent>(player);
        auto &playerState   = playerData.currState;
        bool isPlayerMoving = playerPhysics.dir != Direction::None;
        if (playerState != PlayerState::Alive || !isPlayerMoving) return;
        const float timeToSound = 0.25f;
        m_currTime += dt;
        if (m_currTime > timeToSound)
        {
            em.getSingletonComponent<SfxComponent>().step.sound.play();
            m_currTime = 0;
        }
    }
}