#include "TileObj.h"
#include <iostream>

TileObj::TileObj(Cfg::Textures tex_,sf::IntRect rect_, int pitch_, TileType type_, bool empty_, sf::Vector2f pos_)
    : DrawableObj{}
	, m_type{type_}
	, m_pitch{ pitch_ }
{
	DrawableObj::initializeAsTile(rect_, tex_, pos_);
}

TileObj::~TileObj()
{
}

void TileObj::update(float dt_)
{

	DrawableObj::update(dt_);
}

void TileObj::render(sf::RenderWindow& wnd_)
{

	DrawableObj::render(wnd_);
}

sf::Vector2i TileObj::getTexRectSize()
{
	return (sf::Vector2i)this->GetSize();
}

Cfg::Textures TileObj::getTextureID()
{
	return DrawableObj::getTextureID();
}

sf::Vector2i TileObj::getTexPos()
{
	return (sf::Vector2i)DrawableObj::getTexRectPos();
}

int TileObj::getPitch()
{
	return m_pitch;
}

bool TileObj::isSolid()
{
	return (m_type == TileType::InvisibleAndSolid || m_type == TileType::VisibleAndSolid);
}

bool TileObj::isVisible()
{
	return (m_type == TileType::VisibleAndSolid || m_type == TileType::VisibleAndEmpty);
}

bool TileObj::isEmpty()
{
	return m_type == TileType::InvisibleAndEmpty;
}



TileType TileObj::getType()
{
	return this->m_type;
}

bool operator==(TileObj& lhs_, TileObj& rhs_)
{
	return lhs_.ID() == rhs_.ID();
}
