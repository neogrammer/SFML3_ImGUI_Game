#include "PlayerObj.h"
#include <Tilemap/Tilemap.h>

PlayerObj::PlayerObj() : DrawableObj{}
		, fsmPlayer{}
		, animHandler{ &fsmPlayer, dynamic_cast<DrawableObj*>(this) }
	{
		DrawableObj::initialize("Player.anim", { 49.f,85.f }, Cfg::Textures::PlayerAtlas, { 400.f - 65.f,300.f - 80.f }, { 0.f,0.f });
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

	}


PlayerObj::~PlayerObj()
{
}

void PlayerObj::handleInput()
{
}

void PlayerObj::update(float dt_)
{
	auto* drO = dynamic_cast<DrawableObj*>(this);

	if (((!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))))
	{
		SetVelocity({ 0.f,GetVelocity().y });
		if (m_animName != "Idle")
		{
			//			ChangeAnim("Idle");
			dispatch(fsmPlayer, EventStoppedMoving{});
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			SetVelocity({ 350.f, GetVelocity().y });
			drO->m_facingRight = true;
			if (m_animName != "Moving" && m_animName == "StartedMoving" && m_currentFrame == m_texFramesRight.at("StartedMoving").size() - 1)
			{
				dispatch(fsmPlayer, EventMoveStartFinished{});
			}
			else if (m_animName != "Moving" && m_animName != "StartedMoving")
			{
				dispatch(fsmPlayer, EventStartedMoving{});
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			SetVelocity({ -350.f, GetVelocity().y });
			drO->m_facingRight = false;
			if (m_animName != "Moving" && m_animName == "StartedMoving" && m_currentFrame == m_texFramesRight.at("StartedMoving").size() - 1)
			{
				dispatch(fsmPlayer, EventMoveStartFinished{});
			}
			else if (m_animName != "Moving" && m_animName != "StartedMoving")
			{
				dispatch(fsmPlayer, EventStartedMoving{});
			}
		}
	}

	static float shootSetupElapsed = 0.f;
	static bool shootSetupDone = false;
	static float shootWaitElapsed = 0.f;
	static bool justStoppedShooting = false;
	static float shootElapsed = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{

	
		if (m_animName == "Idle" || m_animName == "Moving")
		{
			dispatch(fsmPlayer, EventStartedShooting{});
			shootSetupElapsed = 0.f;
			shootSetupDone = false;
			shootWaitElapsed = 0.f;
			justStoppedShooting = false;
		}
		else	if(!shootSetupDone)
		{

			shootSetupElapsed += dt_;

			if (shootSetupElapsed > 0.1f)
			{
				dispatch(fsmPlayer, EventShootSetupDone{});
				shootSetupDone = true;
				shootElapsed = 0.f;
				shootWaitElapsed = 0.f;
				shootSetupElapsed = 0.f;
				// FIRE BULLET
			}
		}
		else
		{


				// is shooting already and key is held down
				shootElapsed += dt_;
				if (shootElapsed > 2.f) //fireBulletWait)
				{
					shootElapsed = 0.f;
					shootWaitElapsed = 0.f;

					if (m_animName.find("Shooting") != std::string::npos)
					{
						// FIRE BULLET
						std::cout << "Fire bullet" << std::endl;
					}
				}

		}
	}
	else
	{
		shootElapsed = 0.f;
		shootSetupDone = false;

		if (m_animName == "Shooting")
		{
			shootWaitElapsed += dt_;
			if (shootWaitElapsed > 0.25f)
			{
				{
					shootWaitElapsed = 0.f;
					dispatch(fsmPlayer, EventStoppedShooting());
				}
			}
		}
		else
		{
			dispatch(fsmPlayer, EventShootSetupDone());
		}
	}

	if (!this->m_onGround)
		AdjustVelocity({ 0.f, GRAVITY * dt_ });
	if (GetVelocity().y > 1600.f)
		SetVelocity({ GetVelocity().x, 1600.f });

	animHandler.update(dt_);

	DrawableObj::update(dt_);
}

			/*if (m_animName == "Idle")
			{
				dispatch(fsmPlayer, EventStartedShooting{});
				shootSetupElapsed = 0.f;
			}
			else if (m_animName == "Shooting")
			{
				int i = 0;
			}
			else
			{
				dispatch(fsmPlayer, EventStartedShooting{}, EventShootSetupDone());
				shootSetupElapsed = 0.51f;
			}

		}
		else
		{
			shootSetupElapsed += dt_;

			if (shootSetupElapsed >= 0.5f)
			{
				if (m_animName != "Shooting")
				{
					dispatch(fsmPlayer, EventStartedShooting{}, EventShootSetupDone{});
				}
			}
		}*/
	
	
	  /*	if (m_animName != "Idle")
		{
			dispatch(fsmPlayer, EventStoppedShooting{});
		}*/
    

	//if (this->m_onGround)
	//{
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	//}

	

void PlayerObj::render(sf::RenderWindow& wnd_)
{
	if (m_animName != fsmPlayer.getStateName())
		ChangeAnim(fsmPlayer.getStateName());

	//animHandler.render(wnd_);
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

