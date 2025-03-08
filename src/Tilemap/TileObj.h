#pragma once
#include <GameObjects/DrawableObj.h>
#include "TilemapTypes.h"

class TileObj : public DrawableObj
{
	int m_pitch{ 0 };
	TileType m_type{ TileType::InvisibleAndEmpty };

public:
	TileObj() {};
	TileObj(Cfg::Textures tex_, sf::IntRect rect_, int pitch, TileType type_, bool empty_= false, sf::Vector2f pos_ = {0.f,0.f});
	virtual ~TileObj() override;
	
	TileObj(const TileObj&) = default;
	TileObj& operator=(const TileObj&)=default;
	TileObj(TileObj&&)=default;
	TileObj& operator=(TileObj&&)=default;


	friend bool operator==(TileObj& lhs_, TileObj& rhs_);

	virtual void update(float dt_) override;
	virtual void render(sf::RenderWindow& wnd_);

	sf::Vector2i getTexRectSize();
	Cfg::Textures getTextureID();
	sf::Vector2i getTexPos();

	int getPitch();

	bool isSolid();
	bool isVisible();
	bool isEmpty();

	
	TileType getType();

};