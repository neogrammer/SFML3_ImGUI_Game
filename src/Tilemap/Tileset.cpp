#include "Tileset.h"

void Tileset::AddTile(std::unique_ptr<TileObj> tile_)
{
	m_pitch = tile_->getPitch();
	auto& t = tiles_.emplace_back(std::make_unique<TileObj>(tile_->getTextureID(), sf::IntRect{ (sf::Vector2i)tile_->getTexRectPos(), tile_->getTexRectSize() }, tile_->getPitch(), tile_->getType(), tile_->isEmpty(), tile_->GetPosition()));
}

void Tileset::AddTile(Cfg::Textures tex_, sf::IntRect texRect_, int pitch_, TileType type_, bool empty_, sf::Vector2f pos_)
{
	m_pitch = pitch_;
	auto& t = tiles_.emplace_back(std::make_unique<TileObj>(tex_,texRect_,pitch_,type_,empty_,pos_));
}

std::vector<std::unique_ptr<TileObj>>& Tileset::getTiles()
{
	return tiles_;
}

std::unique_ptr<TileObj> Tileset::copyTile(int index)
{
	auto& tile = tiles_.at(index);
	sf::Vector2i texRectPos = (sf::Vector2i)tile->getTexRectPos();
	sf::Vector2i texRectSize = (sf::Vector2i)tile->getTexRectSize();
	tile->SetSize((sf::Vector2f)tile->getTexRectSize());
	Cfg::Textures texID = tile->getTextureID();
	sf::Vector2i startPos = tile->getTexPos();
	int pitch = tile->getPitch();

	sf::Vector2f pos = tile->GetPosition();

	std::unique_ptr<TileObj> aTile = std::make_unique<TileObj>(texID, sf::IntRect{ texRectPos, texRectSize }, pitch, tile->getType(), tile->isEmpty(), pos);
	aTile->SetSize((sf::Vector2f)tile->getTexRectSize());
	return std::move(aTile);
}


