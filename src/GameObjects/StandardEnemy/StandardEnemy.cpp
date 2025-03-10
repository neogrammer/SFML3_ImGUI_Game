#include "StandardEnemy.h"

StandardEnemy::StandardEnemy() 
	: DrawableObj{}
    , animHandler{ &fsmEnemy, dynamic_cast<DrawableObj*>(this) }
{
	DrawableObj::initialize("Player.anim", { 49.f,85.f }, Cfg::Textures::PlayerAtlas, { 600.f,600.f-178.f + 43.f }, { 0.f,0.f });
	setFrameOffset("Idle", { 44.f,43.f });
	m_frameDelays["Idle"] = 0.13f;
	m_loopDelays["Idle"] = 1.f;
	m_loopWaits = true;

	m_frameDelays["Moving"] = 0.09f;
	m_loopDelays["Moving"] = 0.f;

	m_frameDelays["StartedMoving"] = 0.08f;
	m_loopDelays["StartedMoving"] = 0.f;

	m_frameDelays["StartedShooting"] = 0.03f;
	m_loopDelays["StartedShooting"] = 10.f;

	m_frameDelays["Shooting"] = 2.f;
	m_loopDelays["Shooting"] = 10.f;


	m_frameDelays["MovingAndShooting"] = 0.08f;
	m_loopDelays["MovingAndShooting"] = 0.f;

	m_frameDelays["StartedMovingAndShooting"] = 0.08f;
	m_loopDelays["StartedMovingAndShooting"] = 0.f;
	m_frameDelays["StartedJump"] = 0.6f;
	m_loopDelays["StartedJump"] = 10.f;
	m_frameDelays["Rising"] = 0.6f;
	m_loopDelays["Rising"] = 10.f;
	m_frameDelays["AtJumpTop"] = 0.6f;
	m_loopDelays["AtJumpTop"] = 10.f;
	m_frameDelays["Falling"] = 0.6f;
	m_loopDelays["Falling"] = 10.f;
	m_frameDelays["Landing"] = 0.6f;
	m_loopDelays["Landing"] = 10.f;
	m_frameDelays["StartedJumpAndShooting"] = 0.6f;
	m_loopDelays["StartedJumpAndShooting"] = 10.f;
	m_frameDelays["RisingAndShooting"] = 0.6f;
	m_loopDelays["RisingAndShooting"] = 10.f;
	m_frameDelays["AtJumpTopAndShooting"] = 0.6f;
	m_loopDelays["AtJumpTopAndShooting"] = 10.f;
	m_frameDelays["FallingAndShooting"] = 0.6f;
	m_loopDelays["FallingAndShooting"] = 10.f;
	m_frameDelays["LandingAndShooting"] = 0.6f;
	m_loopDelays["LandingAndShooting"] = 10.f;

	this->m_facingRight = false;
}


StandardEnemy::~StandardEnemy()
{
}

void StandardEnemy::handleInput()
{
}

FSM_Player& StandardEnemy::getFsm()
{
	return fsmEnemy;
}

void StandardEnemy::update(float dt_)
{

	animHandler.update(dt_);

	DrawableObj::update(dt_);
}




void StandardEnemy::render(sf::RenderWindow& wnd_)
{



	//animHandler.render(wnd_);
	DrawableObj::render(wnd_);
}

sf::Vector2i StandardEnemy::getTexRectSize()
{
	return (sf::Vector2i)DrawableObj::getTexRectSize();
}

Cfg::Textures StandardEnemy::getTextureID()
{
	return DrawableObj::getTextureID();
}

sf::Vector2i StandardEnemy::getTexPos()
{
	return (sf::Vector2i)DrawableObj::getTexRectPos();
}
