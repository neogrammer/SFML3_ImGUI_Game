#pragma once
#include <Physics/BBox.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <Resources/Maps.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Resources/Cfg.h>

class GameObject
{
protected:
	sf::Vector2f pos_{}; // 	float x_, y_;
	
	std::vector<sf::Vector2f> sizes_{}; // 	float w_, h_;
	std::vector<size_t> numFrames_{};
	std::vector<std::vector<sf::IntRect>> texFrames_{};
	std::vector<std::vector<sf::Vector2f>> offsets_{};

	std::vector<std::string> animIDs_{};    //	int tx_, ty_, tw_, th_;
	std::vector<bool> isUniDirectional_{};
	std::vector<Cfg::Textures> texIDs_{};

	std::string currID_{ "Invariant" };
	std::string currDir_{ "Uni" };
	size_t currFrame_{ 0 };
	size_t numAnimations_{ 0 };

	size_t getIndex();
	size_t getIndex(const std::string& id_);

public:
	GameObject(const sf::Vector2f& pos, const sf::Vector2f& size);
	virtual ~GameObject();

	// handled in VisibleObject
	virtual void addAnimation() {}


	virtual void Update(float dt_)
	{
		// Default implementation (optional).
		// Often empty if the base class doesn't need to do anything here.
	}
	

	// Called in a fixed-step loop (e.g. 60Hz).
	// Typically for physics or collision checks.
	virtual void FixedUpdate(float fps60_)
	{
		// Default implementation (optional).
	}
	std::unique_ptr<sf::Sprite> sprite();
	virtual void Render(sf::RenderWindow& wnd_);

	//virtual BBox& getBBox(); // current
	//virtual BBox& getBBox(std::string id_, std::string dir_, int index_);
    std::string CurrID();
	std::string CurrDir();
	inline const std::string& CurrDir() const { return currDir_; }

	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);
	void move(sf::Vector2f amt);

};