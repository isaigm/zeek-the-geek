#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
struct AnimationComponent
{
    std::vector<sf::Vector2i> frames;
    float timePerFrame {};
    int currFrame {};
    float currTime {};
};