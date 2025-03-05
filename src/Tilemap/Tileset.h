#pragma once

#include <memory>
#include <vector>
#include "Tile.h"

class Tileset
{
	std::vector<std::unique_ptr<Tile> > tiles_{};

public:
	void AddTile(std::unique_ptr<Tile> tile);
	void AddTile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch);

	std::vector<std::unique_ptr<Tile>>& getTiles();
	std::unique_ptr<Tile> copyTile(int index);

};