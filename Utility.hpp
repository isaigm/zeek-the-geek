#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <format>
#include "cmp/PhysicsComponent.hpp"
#include "man/EntityManager.hpp"
#include "Constants.hpp"
#include "Animations.hpp"
namespace ztg
{
    namespace utils
    {
        static sf::Vector2i toWoorldCoords(sf::Vector2f pos)
        {
            return {int(pos.x) / TILE_SIZE, int(pos.y) / TILE_SIZE};
        }
        static sf::Vector2i toWoorldCoords(float x, float y)
        {
            return {int(x) / TILE_SIZE, int(y) / TILE_SIZE};
        }
        static float getDist(sf::Vector2f p, sf::Vector2f q)
        {
            float dx = p.x - q.x;
            float dy = p.y - q.y;
            return std::sqrt(dx * dx + dy * dy);
        }
        static std::string getKey(sf::Vector2i p)
        {
            return std::format("{},{}", p.x, p.y);
        }
        template <typename T>
        static void moveGivenDirection(Direction dir, sf::Vector2<T> &pos, T offset)
        {
            switch (dir)
            {
            case Direction::Up:
                pos.y -= offset;
                break;
            case Direction::Down:
                pos.y += offset;
                break;
            case Direction::Left:
                pos.x -= offset;
                break;
            case Direction::Right:
                pos.x += offset;
                break;
            case Direction::None:
                break;
            }
        }
        static void activateBomb(EntityManager &em, Entity &e)
        {
            auto &bombState         = em.getComponent<ExplodableStateComponent>(e);
            if (bombState.currState == ExplodableState::Actived) return;
            bombState.currState     = ExplodableState::Actived;
            bombState.timeToExplode = 10.0f;
            em.addComponent<AnimationComponent>(ztg::animations[ztg::BOMB_ACTIVED], e);
        }
    }
}
