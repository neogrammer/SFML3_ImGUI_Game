#pragma once
#include "GameObject.h"
#include <Resources/Cfg.h>

class VisibleObject : public GameObject
{
public:
	VisibleObject(sf::Vector2f size, sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, int numFrames, const std::string& dir, const std::string& animID, std::vector<sf::Vector2f> offsets);

	virtual ~VisibleObject() override {}

	virtual void Render(sf::RenderWindow& wnd_) override;

protected:
	Cfg::Textures textureID_{ Cfg::Textures::Invariant };
	std::vector<sf::Vector2f> offsets{};
};