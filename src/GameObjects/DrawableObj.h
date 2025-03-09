// DrawableObj =  Drawable GameObject
//  Justin Layne Hardee
//  copyright 3-7-2025
// MIT liscense
// Use it, abuse it, don't get used to ti

#pragma once
#include "GObj.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Resources/Cfg.h>


class DrawableObj : public GObj
{
	friend class AnimHandler;
protected:
	bool m_playing{ true };
	bool m_loopWaits{ false };
	bool m_looping{ true };

	bool m_uniDirectional{ false };
	

	std::unordered_map<std::string, float> m_startDelays{};
	std::unordered_map<std::string, float> m_loopDelays{};
	std::unordered_map<std::string, float> m_frameDelays{};

	// Animation Parameters
	std::vector<sf::IntRect>* m_anim{ nullptr };
	std::string m_animName{ "None" };
	size_t m_currentFrame{ (size_t)0 };
	Cfg::Textures m_texture{ Cfg::Textures::Invariant };
	/// <summary>
	/// each animation has a specific point from the tl corner where the image will be displayed to the tl corner of the objects bounding box, in world coords, the frameOffset, one per animation. 
	/// .  can be outside of texture bounds
	/// </summary>
	std::unordered_map<std::string, sf::Vector2f> m_frameOffset{};
	// default position to 0.f,0.f and make size mandatory and size will be constant per animation
	/// <summary>
	/// position and size of animation in the sprite atlas,
	/// </summary>
	std::unordered_map<std::string, std::vector<sf::IntRect>> m_texFramesRight{};
	std::unordered_map<std::string, std::vector<sf::IntRect>> m_texFramesLeft{};
	std::unordered_map<std::string, std::vector<sf::IntRect>> m_texFramesUni{};
	
protected:
	void initialize(const std::string& filepath_, sf::Vector2f size_ = { 50.f,50.f }, Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = sf::Vector2f{ 0.f,0.f });
	void initializeAsTile(sf::IntRect rect_, Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f pos_ = { 0.f,0.f });

public:
	DrawableObj();
	virtual ~DrawableObj() override;
	
	DrawableObj(const DrawableObj&);
	DrawableObj& operator=(const DrawableObj&);
	DrawableObj(DrawableObj&&) = default;
	DrawableObj& operator=(DrawableObj&&)=default;
	bool m_facingRight{ true };



	friend bool operator==(DrawableObj& lhs_, DrawableObj& rhs_);

	void update(float dt_) override;
	virtual void render(sf::RenderWindow& wnd_);

	void ChangeAnim(const std::string& animName);
	void animate();

	inline size_t ID() const { return GObj::ID(); }
	void SetSize(const sf::Vector2f& size_);
	inline sf::Vector2f GetSize() const {
		return GObj::GetSize();
	};
	/// <summary>
	/// Adjust world coordinates a set amount (amount should include the game's frame time 
	/// </summary>
	void AdjustPosition(const sf::Vector2f& amt_);
	/// <summary>
	/// Set to specific coordinate in world coordinates
	/// </summary>
	void SetPosition(const sf::Vector2f& pos_);
	inline sf::Vector2f GetPosition() const {
		return GObj::GetPosition();
	};
	/// <summary>
	/// (acceleration * frametime) passed in, gets added to the velocity
	/// </summary>
	/// <param name="amt"></param>
	void AdjustVelocity(const sf::Vector2f& amt_);
	/// <summary>
	/// Set specific velocity
	/// </summary>
	/// <param name="vel_"></param>
	void SetVelocity(const sf::Vector2f& vel_);
	inline sf::Vector2f GetVelocity() const {
		return GObj::GetVelocity();
	};

	sf::Vector2f getTexRectSize();
	Cfg::Textures getTextureID();
	sf::Vector2f getTexRectPos();
	void setFrameOffset(std::string animName_, sf::Vector2f offset_);
	sf::Vector2f getFrameOffset();

};