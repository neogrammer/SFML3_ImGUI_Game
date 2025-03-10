#ifndef PROJECTILE_H__
#define PROJECTILE_H__
#include "ProjectileTypes.h"
class Projectile
{
	proj::DirType m_dirType;
	proj::DmgType m_dmgType;
	int m_power;
public:
	Projectile() : Projectile{proj::DirType::Horizontal, proj::DmgType::Burst, 1} {}
	Projectile(proj::DirType dir_, proj::DmgType dmg_, int power_) : m_dirType{ dir_ }, m_dmgType{ dmg_ }, m_power{ power_ } {}
	virtual ~Projectile() = 0;
	Projectile(const Projectile&) = default;
	Projectile& operator=(const Projectile&) = default;
	Projectile(Projectile&&) = default;
	Projectile& operator=(Projectile&&) = default;
};

#endif