#pragma once
#include <GameObjects/DrawableObj.h>
#include <Animation/AnimHandler.h>

class StandardEnemy : public DrawableObj
{
	FSM_Player fsmEnemy;
	AnimHandler animHandler;
	int health{10}, healthmax{10};
	const sf::Color masked{ sf::Color(200, 12,12,255) };
	const sf::Color normal{ sf::Color::White };

	bool takingDmg{ false };
	float hitWaitDelay{0.05f};
	float hitWaitElapsed{0.f};
	bool justDied{ false };
	sf::Color currMask{ normal };
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
	sf::Color DetermineMaskColor(float dt_);
	void GetHit(int power);

};

