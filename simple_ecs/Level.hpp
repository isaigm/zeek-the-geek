#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/TileLayer.hpp>

struct Level
{
	Level(std::string path)
	{
		tmx::Map map;
		if (!map.load(path)) throw(std::runtime_error("Cannot load the file"));

	}
private:
	std::vector<uint16_t> m_tiles;
};