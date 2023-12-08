#pragma once
#include <SFML/Graphics.hpp>
struct Hud
{
    struct Label
    {
        Label(sf::Font &font, std::string name)
        {
            m_text.setFont(font);
            m_text.scale(0.4, 0.4);
            m_text.setFillColor(sf::Color::Black);
            m_name = name;
        }
        void setPosition(float x, float y)
        {
            m_text.setPosition(x, y);
        }
        void update(int offset)
        {
            m_value += offset;
        }
        void setValue(int value)
        {
            m_value = value;
        }
        void render(sf::RenderTarget &rt)
        {
            m_text.setString(getFullName());
            rt.draw(m_text);
        }
        void setSpaces(int spaces)
        {
            m_spaces = spaces;
        }
        private:
            std::string getSpaces()
            {
                std::string result {};
                for(int i = 0; i < m_spaces; i++)
                {
                    result += " ";
                }
                return result;
            }
            std::string getFullName()
            {
                return  m_name + getSpaces() + std::to_string(m_value);
            }
            int         m_value {};
            int         m_spaces;
            sf::Text    m_text;
            std::string m_name{};
    };
    Hud() : m_level(m_font, "Level"), m_bonus(m_font, "Bonus"), m_score(m_font, "Score")
    {
       if(!m_font.loadFromFile("assets/font.ttf")) throw std::runtime_error("cannot load the font");
       
       m_score.setPosition(506, 5);
       m_level.setPosition(506, 50);
       m_bonus.setPosition(506, 90);
       m_bonus.setSpaces(5);
       m_level.setSpaces(6);
       m_score.setSpaces(6);
    }
    void render(sf::RenderTarget &rt)
    {
        m_score.render(rt);
        m_level.render(rt);
        m_bonus.render(rt);
    }
    Label &getLevel()
    {
        return m_level;
    }
    Label &getBonus()
    {
        return m_bonus;
    }
private:
    sf::Font m_font;
    Label    m_level;
    Label    m_bonus;
    Label    m_score;
};