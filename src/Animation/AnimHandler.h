#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameObjects/DrawableObj.h>
#include <Event/EventTypes.h>

#include <FSM/PlayerAnimFSM.h>


class AnimHandler
{
	bool alreadyStarted{ false };
	float startElapsed{ 0.f };
	float frameElapsed{ 0.f };
	float loopElapsed{ 0.f };
public:
	DrawableObj* parent;
	FSM_Player* ownerFSM;
	std::vector<PlayerEventVar> events;

	AnimHandler(FSM_Player* fsm_, DrawableObj* parent_); 
	
	~AnimHandler();
	AnimHandler(const AnimHandler&) = default;
	AnimHandler& operator=(const AnimHandler&) = default;
	AnimHandler(AnimHandler&&) = default;
	AnimHandler& operator=(AnimHandler&&) = default;

	void update(float dt_);
	void render(sf::RenderWindow& wnd_);

};
