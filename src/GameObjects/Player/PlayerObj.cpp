#include "PlayerObj.h"
#include <Tilemap/Tilemap.h>
PlayerObj::PlayerObj()
	: DrawableObj{}
{
	DrawableObj::initialize("Player.anim", { 49.f,85.f }, Cfg::Textures::PlayerAtlas, { 400.f - 65.f,300.f - 80.f }, { 0.f,0.f });
	setFrameOffset("IdleRight", { 44.f,43.f });
	setFrameOffset("IdleLeft", { 44.f,43.f });

}

PlayerObj::~PlayerObj()
{
}

void PlayerObj::handleInput()
{
}

void PlayerObj::update(float dt_)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		SetVelocity({ 300.f, GetVelocity().y });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		SetVelocity({ -300.f, GetVelocity().y });
	if (((!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))))
		SetVelocity({0.f,GetVelocity().y});

	if (!this->m_onGround)
		AdjustVelocity({ 0.f, GRAVITY * dt_});
	if (GetVelocity().y > 1600.f)
		SetVelocity({ GetVelocity().x, 1600.f });
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

void PlayerObj::SetOnGround(bool cond_)
{
	m_onGround = cond_;
}

