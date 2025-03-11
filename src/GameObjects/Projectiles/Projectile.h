#ifndef PROJECTILE_H__
#define PROJECTILE_H__
#include "ProjectileTypes.h"
#include <GameObjects/DrawableObj.h>
class Projectile : public DrawableObj
{
protected:
	proj::DirType m_dirType;
	proj::DmgType m_dmgType;
	int m_power;
	bool m_alive{ true };
public:
	Projectile(sf::Vector2f pos_ = { 0.f,0.f }) : Projectile{ proj::DirType::Horizontal, proj::DmgType::Burst, 1, pos_ }
	{
		int i = 0;
	}
	Projectile(proj::DirType dir_, proj::DmgType dmg_, int power_, sf::Vector2f pos_ = { 0.f,0.f }) : DrawableObj{}, m_dirType{ dir_ }, m_dmgType{ dmg_ }, m_power{ power_ }
	{
		DrawableObj::initialize("BusterBullet.anim", { 27.f, 17.f }, Cfg::Textures::BusterBullet, pos_, { 0.f,0.f });
	}
	virtual ~Projectile() = 0;
	Projectile(const Projectile&) = default;
	Projectile& operator=(const Projectile&) = default;
	Projectile(Projectile&&) = default;
	Projectile& operator=(Projectile&&) = default;

	virtual void update(float dt_) override = 0;
	virtual void render(sf::RenderWindow& dt_) override;

	bool isAlive() { return m_alive; }
	void setAlive(bool cond_) { m_alive = cond_; }

};

#endif