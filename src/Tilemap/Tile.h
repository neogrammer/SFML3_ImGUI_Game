#pragma once
#include <GameObjects/VisibleObject.h>

class Tile : public VisibleObject
{
	int pitch_;
	bool visible_{ true };
public:
	Tile(sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch);
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


};