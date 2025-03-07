#pragma once
#include "GameObject.h"
#include <Resources/Cfg.h>

class VisibleObject : public GameObject
{
public:
	VisibleObject(sf::Vector2f size, sf::Vector2f texRectSize, Cfg::Textures texID, sf::Vector2f startPos, int pitch, int numFrames, const std::string& dir, const std::string& animID, std::vector<sf::Vector2f> offsets);

	virtual ~VisibleObject() override {}

	virtual void Render(sf::RenderWindow& wnd_) override;
	sf::Vector2i getFrameSize();
	sf::Vector2i getFrameSize(const std::string& animID);
	virtual sf::IntRect getTexFrame(const std::string& animID, const std::string& dir, size_t frameNum);
protected:

	virtual size_t getIndex() const override;
	virtual size_t getIndex(const std::string& id_) override;



};