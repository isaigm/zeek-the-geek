#pragma once
#include <SFML/Graphics.hpp>
struct TileSet
{
	TileSet(std::string path, int width, int height, int tileWidth, int tileHeight) : 
		m_width(width), m_height(height), m_tileWidth(tileWidth), m_tileHeight(tileHeight)
	{
		if (!m_texture.loadFromFile(path)) throw std::runtime_error("Cannot load the file");
		
	}
private:
	sf::Texture m_texture;
	int m_tileWidth, m_tileHeight, m_width, m_height;

};