#include "AnimHandler.h"

void AnimHandler::render(sf::RenderWindow& wnd_)
{
	sf::IntRect texRect = parent->m_texFramesRight[parent->m_animName].at(parent->m_currentFrame);
	sf::Vector2f pos = { parent->GetPosition().x - parent->m_frameOffset[parent->m_animName].x, parent->GetPosition().x - parent->m_frameOffset[parent->m_animName].y };
	pos.x -= parent->m_frameOffset[parent->m_animName].x;
	pos.y -= parent->m_frameOffset[parent->m_animName].y;
	Cfg::Textures texID = parent->getTextureID();

	sf::Sprite spr{ Cfg::textures.get((int)texID) };
	spr.setPosition(pos);
	spr.setTextureRect(texRect);

	wnd_.draw(spr);
}

AnimHandler::AnimHandler(FSM_Player* fsm_, DrawableObj* parent_)
	: ownerFSM{ fsm_ }, parent{ parent_ }, events{ std::vector<PlayerEventVar>{} } {}

AnimHandler::~AnimHandler()
{
}

void AnimHandler::update(float dt_)
{
	bool animate = false;
	if (parent->m_playing)
	{
		if (!parent->m_startDelays.empty() && !alreadyStarted)
		{
			if (parent->m_startDelays[parent->m_animName] != 0.f)
			{
				startElapsed += dt_;
				if (startElapsed >= parent->m_startDelays[parent->m_animName])
				{
					startElapsed = 0.f;
					alreadyStarted = true;
					animate = true;
				}
			}
			else
			{
				alreadyStarted = true;
				frameElapsed = 0.f;
				animate = false;
			}
		}
		else	if (parent->m_currentFrame == ((parent->m_facingRight) ? parent->m_texFramesRight[parent->m_animName].size() : parent->m_texFramesLeft[parent->m_animName].size()) - 1)
		{
			if (parent->m_loopWaits)
			{
				loopElapsed += dt_;
				if (loopElapsed > parent->m_loopDelays[parent->m_animName])
				{
					loopElapsed = 0.f;
					animate = true;
				}
			}
			else
			{
				if (parent->m_looping)
				{
					parent->m_currentFrame = 0;
				}
			}
		}
		else
		{
			frameElapsed += dt_;
			if (frameElapsed >= parent->m_frameDelays[parent->m_animName])
			{
				frameElapsed = 0.f;
				animate = true;
			}
		}

		if (animate == true)
			parent->animate();

	}
	for (auto& evt : events)
	{
		dispatch(*ownerFSM, evt);
	}



	events.clear();
}
