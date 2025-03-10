#pragma once
#include <GameObjects/DrawableObj.h>
#include <Animation/AnimHandler.h>

class StandardEnemy : public DrawableObj
{
	FSM_Player fsmEnemy;
	AnimHandler animHandler;
public:

	StandardEnemy();
	virtual ~StandardEnemy() override;

	StandardEnemy(const StandardEnemy&) = delete;
	StandardEnemy& operator=(const StandardEnemy&) = delete;
	StandardEnemy(StandardEnemy&&) = delete;
	StandardEnemy& operator=(StandardEnemy&&) = delete;

	void handleInput();

	FSM_Player& getFsm();
	void update(float dt_) override final;
	virtual void render(sf::RenderWindow& wnd_) override final;

	sf::Vector2i getTexRectSize();
	Cfg::Textures getTextureID();
	sf::Vector2i getTexPos();

};

