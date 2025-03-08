#include "PlayerObj.h"

PlayerObj::PlayerObj()
	: DrawableObj{}
{
	DrawableObj::initialize("Player.anim", { 130.f,160.f }, Cfg::Textures::PlayerAtlas, { 400.f - 65.f,300.f - 80.f }, { 0.f,0.f });

}

PlayerObj::~PlayerObj()
{
}

void PlayerObj::update(float dt_)
{

	DrawableObj::update(dt_);
}

void PlayerObj::render(sf::RenderWindow& wnd_)
{

	DrawableObj::render(wnd_);
}

sf::Vector2i PlayerObj::getTexRectSize()
{
	return (sf::Vector2i)DrawableObj::getTexRectSize();
}

Cfg::Textures PlayerObj::getTextureID()
{
	return DrawableObj::getTextureID();
}

sf::Vector2i PlayerObj::getTexPos()
{
	return (sf::Vector2i)DrawableObj::getTexRectPos();
}
