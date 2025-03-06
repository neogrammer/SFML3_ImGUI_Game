#pragma once
#include <GameObjects/VisibleObject.h>
#include "TilemapTypes.h"

class Tile : public VisibleObject
{
	int type_{ 0 }; // 0 empty, 1 solid, 2 static, 3 is invisibleAndSolid
	int pitch_{ 1 }; // tileset's pitch
	bool visible_{ true };
public:
	Tile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, bool visible, int type);
	~Tile() override final {}

	void Render(sf::RenderWindow& wnd_) override final;

	sf::Vector2f getSize();
	sf::Vector2i getTexRectSize();
	sf::Vector2f getPos();
	sf::Vector2i getTexPos();
	int getPitch();
	Cfg::Textures getTextureID();
	void setVisible(bool cond);
	bool isVisible();
	int getType() {
		return type_;
	}
	void setType(int type)
	{
		type_ = type;
	}


};