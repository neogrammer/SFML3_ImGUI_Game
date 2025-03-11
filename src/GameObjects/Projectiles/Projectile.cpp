#include "Projectile.h"

Projectile::~Projectile() {}

void Projectile::render(sf::RenderWindow& wnd_)
{
	sf::Sprite aSprite{ Cfg::textures.get((int)this->getTextureID()) };
	aSprite.setTextureRect({ sf::Vector2i{(int)this->getTexRectPos().x, (int)this->getTexRectPos().y}, sf::Vector2i{ (int)(this->getTexRectSize().x),(int)(this->getTexRectSize().y) } });
	aSprite.setPosition({ this->GetPosition().x - this->getFrameOffset().x, this->GetPosition().y - this->getFrameOffset().y , });
	wnd_.draw(aSprite);

	DrawableObj::render(wnd_);
}
