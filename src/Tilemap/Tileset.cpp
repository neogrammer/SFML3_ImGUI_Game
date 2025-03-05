#include "Tileset.h"

void Tileset::AddTile(std::unique_ptr<Tile> tile)
{
	tiles_.emplace_back(std::make_unique<Tile>( (sf::Vector2f)tile->getTexRectSize(), tile->getTextureID(), (sf::Vector2f)tile->getTexPos(), tile->getPitch() ));
}

void Tileset::AddTile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch)
{
	std::unique_ptr<Tile> aTile = std::make_unique<Tile>(texRectSize, texID, startPos, pitch);
	tiles_.emplace_back(std::move(aTile));
}

std::vector<std::unique_ptr<Tile>>& Tileset::getTiles()
{
	return tiles_;
}

std::unique_ptr<Tile> Tileset::copyTile(int index)
{
	auto& tile = tiles_.at(index);
	sf::Vector2i texRectSize = tile->getTexRectSize();
	Cfg::Textures texID = tile->getTextureID();
	sf::Vector2i startPos = tile->getTexPos();
	int pitch = tile->getPitch();

	sf::Vector2f pos = tile->getPos();

	std::unique_ptr<Tile> aTile = std::make_unique<Tile>((sf::Vector2f)texRectSize, texID, (sf::Vector2f)startPos, pitch);
	aTile->setPos(pos);

	return std::move(aTile);
}


