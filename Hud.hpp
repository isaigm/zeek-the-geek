#pragma once
#include <SFML/Graphics.hpp>
#include "Label.hpp"
namespace ztg
{
    struct Hud
    {
        Hud();
        void render(sf::RenderTarget &rt);
        Label &getLevel();
        Label &getBonus();
        Label &getScore();

    private:
        sf::Font m_font;
        Label m_level;
        Label m_bonus;
        Label m_score;
    };
}
