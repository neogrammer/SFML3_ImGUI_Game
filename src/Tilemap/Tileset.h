#pragma once
#include <memory>
#include <vector>
#include "TileObj.h"

class Tileset
{
	std::vector<std::unique_ptr<TileObj> > tiles_{};
	int m_pitch{ 0 };
public:
	void AddTile(std::unique_ptr<TileObj> tile_);
	void AddTile(Cfg::Textures tex_, sf::IntRect texRect_, int pitch_, TileType type_, bool empty_, sf::Vector2f pos_);

	std::vector<std::unique_ptr<TileObj>>& getTiles();
	std::unique_ptr<TileObj> copyTile(int index);

};