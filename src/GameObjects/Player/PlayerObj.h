#pragma once
#include <GameObjects/DrawableObj.h>
#include <Tilemap/TilemapTypes.h>


class PlayerObj : public DrawableObj
{

public:
	PlayerObj();
	virtual ~PlayerObj() override;

	PlayerObj(const PlayerObj&)=delete;
	PlayerObj& operator=(const PlayerObj&)=delete;
	PlayerObj(PlayerObj&&)=delete;
	PlayerObj& operator=(PlayerObj&&)=delete;

	virtual void update(float dt_) override;
	virtual void render(sf::RenderWindow& wnd_);

	sf::Vector2i getTexRectSize();
	Cfg::Textures getTextureID();
	sf::Vector2i getTexPos();
};