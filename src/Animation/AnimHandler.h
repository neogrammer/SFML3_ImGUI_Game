#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameObjects/DrawableObj.h>
#include <Event/EventTypes.h>

#include <FSM/FSM.h>

template <class FSM_TYPE, class STATE_VAR>
class AnimHandler
{
	bool alreadyStarted{ false };
	float startElapsed{ 0.f };
	float frameElapsed{ 0.f };
	float loopElapsed{ 0.f };
public:
	DrawableObj* parent;


	FSM_TYPE* ownerFSM;


	std::vector<PlayerEventVar> events;

//	AnimHandler<FSM_TYPE, STATE_VAR>() : ownerFSM{ nullptr }, parent{ nullptr }, events{ std::vector<PlayerEventVar>{} } {}

	AnimHandler<FSM_TYPE, STATE_VAR>(FSM_TYPE* fsm_, DrawableObj* parent_) : ownerFSM{ fsm_ }, parent{ parent_ }, events{ std::vector<PlayerEventVar>()} {}


	~AnimHandler() = default;

	void update(float dt_)
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

	void render(sf::RenderWindow& wnd_)
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

};
