#pragma once
#include <GameObjects/DrawableObj.h>
#include <Tilemap/TilemapTypes.h>
#include <FSM/PlayerAnimFSM.h>
#include <Animation/AnimHandler.h>

class Tilemap;
class TileObj;
class Projectile;
class PlayerObj : public DrawableObj
{
	const int MAXBULLETS = 5;
	bool m_onGround{ false };
	const int GRAVITY{ 3200 };
	bool rising{ false };
	FSM_Player fsmPlayer;
	bool leftPressed{ false }, rightPressed{ false }, upPressed{ false }, downPressed{ false };

	std::vector<std::shared_ptr<Projectile>> m_bullets;

	AnimHandler animHandler;
public:
	
	PlayerObj(); 
	virtual ~PlayerObj() override;

	PlayerObj(const PlayerObj&)=delete;
	PlayerObj& operator=(const PlayerObj&)=delete;
	PlayerObj(PlayerObj&&)=delete;
	PlayerObj& operator=(PlayerObj&&)=delete;

	void handleInput();
	std::shared_ptr<Projectile> CreateBullet();
	void UpdateDPad(bool* pressed);
	std::vector<std::shared_ptr<Projectile>>& getBullets();


	FSM_Player& getFsm();

	template<typename EVT>
	void disp(EVT event)
	{

		dispatch(fsmPlayer, event);
	};
	void update(float dt_) override final;

	virtual void render(sf::RenderWindow& wnd_) override final;

	sf::Vector2i getTexRectSize();
	Cfg::Textures getTextureID();
	sf::Vector2i getTexPos();

	void SetOnGround(bool cond_);
	inline bool GetOnGround()
	{
		return m_onGround;
	};
};

