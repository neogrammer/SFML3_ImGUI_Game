#pragma once
//#include <GameObjects/StaticObject.h>
#include <Resources/Cfg.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class Tile // : public StaticObject
{
	friend class Tilemap;
private:
		bool solid{ false };
		sf::Vector2f pos{}; // 
		float x_, y_; 
		sf::Vector2f size{}; // 
		float w_, h_;

		std::vector<sf::IntRect> texFrames{};
		int tx_, ty_, tw_, th_;


		size_t currFrame_{ 0 };
		size_t numFrames_{ 1 };

		Cfg::Textures texID_{ Cfg::Textures::Invariant };
		Cfg::Textures type_;
public:
	Tile(float x_ = 0.f, float y_ = 0.f, float w_ = 50.f, float h_ = 50.f);
	Tile(bool solid_, Cfg::Textures type, float x_ = 0.f, float y_ = 0.f, float w_ = 50.f, float h_ = 50.f,
		int tx_ = 0.f, int ty_ = 0.f, int tw_ = 50.f, int th_ = 50.f);
	Tile(sf::FloatRect worldRect_, sf::IntRect texRect_, bool solid_, Cfg::Textures type);
	Tile(sf::IntRect texRect_, bool solid_, Cfg::Textures type);

	~Tile();
	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;
	Tile& operator=(Tile&&) = default;
	Tile(Tile&&) = default;

	// override the update if you need it
	virtual void Update(float dt_);

	virtual void Render(sf::RenderWindow& wnd_);
	void SetSolid(bool solid_);
	inline bool getSolid() { return solid; }
	inline float & x() { return x_; }
	inline float & y() { return y_; }
	inline float & w() { return w_; }
	inline float & h() { return h_; }
	inline int& tx() { return tx_; }
	inline int& ty() { return ty_; }
	inline int& tw() { return tw_; }
	inline int& th() { return th_; }
	sf::FloatRect worldRect();
	sf::IntRect texRect();
	inline int& currFrame() { return currFrame_; }
	std::unique_ptr<sf::Sprite> getSprite();

};