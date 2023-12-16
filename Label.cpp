#include "Label.hpp"
namespace ztg
{
    Label::Label(sf::Font &font, std::string name)
    {
        m_text.setFont(font);
        m_text.scale(0.4, 0.4);
        m_text.setFillColor(sf::Color::Black);
        m_name = name;
    }
    void Label::setPosition(float x, float y)
    {
        m_text.setPosition(x, y);
    }
    void Label::update(int offset)
    {
        m_value += offset;
    }
    void Label::setValue(int value)
    {
        m_value = value;
    }
    void Label::render(sf::RenderTarget &rt)
    {
        m_text.setString(getFullName());
        rt.draw(m_text);
    }
    void Label::setSpaces(int spaces)
    {
        m_spaces = spaces;
    }

    std::string Label::getSpaces()
    {
        std::string result{};
        for (int i = 0; i < m_spaces; i++)
        {
            result += " ";
        }
        return result;
    }
    std::string Label::getFullName()
    {
        return m_name + getSpaces() + std::to_string(m_value);
    }
}