#include "GameManager.hpp"
namespace ztg
{
    GameManager::GameManager() : m_tileSet("assets/spritesheet.png", TILE_SIZE, TILE_SIZE)
    {
    }
    void GameManager::loadLevel(EntityManager &em, int level)
    {
        auto path = getPathLevel(level);
        m_currentLevel.loadFromFile(path);
        auto addEntitiy = [&](int tileID, int x, int y)
        {
            auto &entity = em.createEntity();
            entity.addTag(Tags::OBJECT);
            RenderComponent renderComponent;
            m_tileSet.setTile(renderComponent.sprite, m_currentLevel.getTileAt(x, y) - 1); // tiled specific
            PhysicsComponent physicsComponent;
            physicsComponent.pos = {float(x * TILE_SIZE), float(y * TILE_SIZE)};
            em.addComponent<RenderComponent>(std::move(renderComponent), entity);
            em.addComponent<PhysicsComponent>(std::move(physicsComponent), entity);
            int tag = TilesID::getTag(tileID);
            switch (tag)
            {
            case Tags::PLANT:
            {
                PlantStateComponent state;
                state.currState = TilesID::getPlantState(tileID);
                em.addComponent<PlantStateComponent>(std::move(state), entity);
                break;
            }
            case Tags::PLAYER:
            {
                PlayerStateComponent state;
                em.addComponent<PlayerStateComponent>(std::move(state), entity);
                break;
            }
            break;
            default:
                break;
            }
            entity.addTag(tag);
            if (entity.hasTag(Tags::CRYSTAL) || entity.hasTag(Tags::BOMB))
            {
                ExplodableStateComponent state;
                em.addComponent<ExplodableStateComponent>(std::move(state), entity);
            }
        };
        bool playerFound = false;
        sf::Vector2i playerPos;
        auto &levelComponent = em.getSingletonComponent<LevelComponent>();
        levelComponent.width = m_currentLevel.getWidth();
        levelComponent.height = m_currentLevel.getHeight();
        levelComponent.playableArea = levels[level];
        levelComponent.mapIds.clear();
        levelComponent.updatePlayerCollisions = false;

        for (int y = 0; y < m_currentLevel.getHeight(); y++)
        {
            for (int x = 0; x < m_currentLevel.getWidth(); x++)
            {
                auto tileID = m_currentLevel.getTileAt(x, y);
                if (TilesID::isEmpty(tileID))
                {
                    em.getSingletonComponent<LevelComponent>().addId(LevelComponent::EMPTY);
                    continue;
                }
                else if (TilesID::isPlayer(tileID))
                {
                    playerFound = true;
                    playerPos = {x, y};
                    em.getSingletonComponent<LevelComponent>().playerPos = playerPos;
                    em.getSingletonComponent<LevelComponent>().playerId = em.getSize();
                }
                em.getSingletonComponent<LevelComponent>().addId(em.getSize());
                addEntitiy(tileID, x, y);
            }
        }
        if (!playerFound)
            throw std::runtime_error("cannot find the player");
    }
    std::string GameManager::getPathLevel(int level)
    {
        return "assets/level" + std::to_string(level) + ".tmx";
    }

}