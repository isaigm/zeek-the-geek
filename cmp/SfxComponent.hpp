#pragma once
#include <SFML/Audio.hpp>
struct SfxComponent
{
    struct Sfx
    {
        sf::SoundBuffer sb;
        sf::Sound sound;
    };
    Sfx pick;
    Sfx grab;
    Sfx detonate;
    Sfx poisoned;
    Sfx crystal;
    Sfx step;
};