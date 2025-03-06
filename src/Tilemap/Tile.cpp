#include "Tile.h"

Tile::Tile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, bool visible, int type)
	: VisibleObject(texRectSize, texRectSize, texID, startPos, pitch, 1, "Uni", "Tileset", std::vector<sf::Vector2f>{})
	, pitch_{pitch}
	, visible_{visible}
	, type_{type}
{

}

void Tile::Render(sf::RenderWindow& wnd_)
{
	wnd_.draw(*sprite());
}

sf::Vector2f Tile::getSize()
{
	return this->sizes_.at(getIndex());
}

sf::Vector2i Tile::getTexRectSize()
{
	return texFrames_.at(getIndex()).at(currDir_).at(currFrame_).size;
}

sf::Vector2f Tile::getPos()
{
	return pos_;
}

sf::Vector2i Tile::getTexPos()
{
	return texFrames_.at(getIndex()).at(currDir_).at(currFrame_).position;
}

int Tile::getPitch()
{
	return pitch_;
}

Cfg::Textures Tile::getTextureID()
{
	return textureID_;
}

void Tile::setVisible(bool cond)
{
	visible_ = cond;
}

bool Tile::isVisible()
{
	return visible_;
}
