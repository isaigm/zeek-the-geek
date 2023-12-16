#pragma once
#include <SFML/Graphics.hpp>
namespace ztg
{
    struct Label
    {
        Label(sf::Font &font, std::string name);
        void setPosition(float x, float y);
        void setSpaces(int spaces);
        void setValue(int value);
        void update(int offset);
        void render(sf::RenderTarget &rt);
    private:
        std::string getSpaces();
        std::string getFullName();
        int m_value{};
        int m_spaces;
        sf::Text m_text;
        std::string m_name{};
    };
}
