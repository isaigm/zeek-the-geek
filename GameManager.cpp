#include "GameManager.hpp"
#include "Animations.hpp"
namespace ztg
{
    GameManager::GameManager() : m_tileSet("assets/spritesheet.png", TILE_SIZE, TILE_SIZE)
    {
    }
    void GameManager::loadSounds(EntityManager &em)
    {
        auto &sfx = em.getSingletonComponent<SfxComponent>();
        loadSfx(sfx.pick,     "assets/pick.wav");
        loadSfx(sfx.grab,     "assets/grab.wav");
        loadSfx(sfx.detonate, "assets/detonate.wav");
        loadSfx(sfx.poisoned, "assets/poisoned.wav");
        loadSfx(sfx.crystal,  "assets/crystal.wav");
        loadSfx(sfx.step,     "assets/step.wav");
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
            
            int tag = TilesID::getTag(tileID);
            entity.addTag(tag);
            if (entity.hasTag(Tags::MONSTER))
            {
                em.addComponent<MonsterDataComponent>(MonsterDataComponent{}, entity);
            }
            else if (entity.hasTag(Tags::PLANT))
            {
                PlantDataComponent data;
                data.currState = TilesID::getPlantState(tileID);
                em.addComponent<PlantDataComponent>(std::move(data), entity);
                entity.addTag(Tags::REMOVABLE);
            }
            else if (entity.hasTag(Tags::ROTTEN_APPLE))
            {
                em.addComponent<AnimationComponent>(animations[ROTTEN_APPLE], entity);
            }
            else if (entity.hasTag(Tags::PLAYER))
            {
                em.addComponent<PlayerDataComponent>(PlayerDataComponent{}, entity);
            }
            else if (entity.hasTag(Tags::CRYSTAL) || entity.hasTag(Tags::BOMB))
            {
                em.addComponent<ExplodableDataComponent>(ExplodableDataComponent{}, entity);
            }
            em.addComponent<RenderComponent>(std::move(renderComponent), entity);
            em.addComponent<PhysicsComponent>(std::move(physicsComponent), entity);
        };
        bool playerFound = false;
        sf::Vector2i playerPos;
        auto &levelComponent                  = em.getSingletonComponent<LevelComponent>();
        levelComponent.width                  = m_currentLevel.getWidth();
        levelComponent.height                 = m_currentLevel.getHeight();
        levelComponent.updatePlayerCollisions = false;
        levelComponent.mapIds.clear();

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
                    playerPos   = {x, y};
                    em.getSingletonComponent<LevelComponent>().playerPos = playerPos;
                    em.getSingletonComponent<LevelComponent>().playerId  = em.getSize();
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

    void GameManager::loadSfx(SfxComponent::Sfx &sfx, std::string path)
    {
        if (!sfx.sb.loadFromFile(path))
        {
            throw std::runtime_error("cannot load the sound effect");
        }
        sfx.sound.setBuffer(sfx.sb);
    }
}