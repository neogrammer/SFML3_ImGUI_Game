#pragma once
#include "GameObject.h"

class InvisibleObject : public GameObject
{
public:
	InvisibleObject(sf::Vector2f size) : GameObject(size) {}
	virtual ~InvisibleObject() override = default;

	virtual void Render(sf::RenderWindow& wnd_) override {}
};