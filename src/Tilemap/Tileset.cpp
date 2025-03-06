#include "Tileset.h"

void Tileset::AddTile(std::unique_ptr<Tile> tile)
{
	auto& t = tiles_.emplace_back(std::make_unique<Tile>( (sf::Vector2f)tile->getTexRectSize(), tile->getTextureID(), (sf::Vector2f)tile->getTexPos(), tile->getPitch() , tile->isVisible(), tile->getType()));
	t->setVisible(tile->isVisible());
	t->setType(tile->getType());
}

void Tileset::AddTile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, bool visible_, int type_)
{
	std::unique_ptr<Tile> aTile = std::make_unique<Tile>(sf::Vector2f{ texRectSize }, texID, startPos, pitch, visible_, type_);
	auto& t = tiles_.emplace_back(std::move(aTile));
	t->setVisible(visible_);
	t->setType(type_);
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

	std::unique_ptr<Tile> aTile = std::make_unique<Tile>((sf::Vector2f)texRectSize, texID, (sf::Vector2f)startPos, pitch, tile->isVisible(), tile->getType());
	aTile->setPos(pos);
	aTile->setVisible((tile->getType() == 0 || tile->getType() == 3) ? false : true);
	aTile->setType(tile->getType());

	return std::move(aTile);
}


