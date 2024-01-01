#include "Hud.hpp"
namespace ztg
{
    Hud::Hud() : m_level(m_font, "Level"), m_bonus(m_font, "Bonus"), m_score(m_font, "Score")
    {
        if (!m_font.loadFromFile("assets/font.ttf"))
            throw std::runtime_error("cannot load the font");

        m_score.setPosition(1020, 10);
        m_level.setPosition(1020, 95);
        m_bonus.setPosition(1020, 185);
        m_bonus.setSpaces(5);
        m_level.setSpaces(6);
        m_score.setSpaces(6);
    }
    void Hud::render(sf::RenderTarget &rt)
    {
        m_score.render(rt);
        m_level.render(rt);
        m_bonus.render(rt);
    }
    Label &Hud::getLevel()
    {
        return m_level;
    }
    Label &Hud::getBonus()
    {
        return m_bonus;
    }
    Label &Hud::getScore()
    {
        return m_score;
    }
}