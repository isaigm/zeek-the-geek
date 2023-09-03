#pragma once
#include <iostream>
#include <vector>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
struct Level
{
	Level(std::string path)
	{
		tmx::Map map;
		if (!map.load(path)) throw std::runtime_error("Cannot load the file");
		const auto& layers = map.getLayers();
		const auto& layer = layers[0];
		const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();		
		const auto& dim = map.getTileCount();
		m_width = dim.x;
		m_height = dim.y;
		for (int i = 0; i < tiles.size(); i++)
		{
			m_tiles.push_back(tiles[i].ID);
		}
	}
	uint16_t getTileAt(int x, int y)
	{
		int idx = x + y * m_width;
		assert(idx < m_tiles.size());
		return m_tiles[idx];
	}
private:
	std::vector<uint16_t> m_tiles;
	int m_width, m_height;
};