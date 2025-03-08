#pragma once
#include <GameObjects/DrawableObj.h>
#include <Tilemap/TilemapTypes.h>
class Tilemap;
class TileObj;
class PlayerObj : public DrawableObj
{
	bool m_facingRight{ true };
	bool m_onGround{ false };
	const int GRAVITY{ 3200 };
public:
	PlayerObj();
	virtual ~PlayerObj() override;

	PlayerObj(const PlayerObj&)=delete;
	PlayerObj& operator=(const PlayerObj&)=delete;
	PlayerObj(PlayerObj&&)=delete;
	PlayerObj& operator=(PlayerObj&&)=delete;

	void handleInput();

	virtual void update(float dt_) override;
	virtual void render(sf::RenderWindow& wnd_);

	sf::Vector2i getTexRectSize();
	Cfg::Textures getTextureID();
	sf::Vector2i getTexPos();

	void SetOnGround(bool cond_);

};