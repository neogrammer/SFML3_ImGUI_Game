#include "DrawableObj.h"
#include <iostream>
#include <fstream>
#include <GameObjects/Projectiles/Projectile.h>
bool operator==(DrawableObj& lhs_, DrawableObj& rhs_)
{
	return lhs_.ID() == rhs_.ID();
}


void DrawableObj::initialize(const std::string& filepath_, sf::Vector2f size_, Cfg::Textures tex_, sf::Vector2f pos_, sf::Vector2f vel_)
{
	GObj::initialize(size_, pos_, vel_);
	m_texture = tex_;

	std::ifstream iFile;

	// should be a .anim file
	iFile.open("Assets/Animations/" + filepath_);

	if (!iFile.is_open() || !iFile.good())
	{
		std::cout << "DrawableObject::initialize() : File not loaded properly for Object ID " << this->ID() << std::endl;
		return;
	}
	else
	{
		// file loaded in correctly
		// STRUCTURE EXPECTED
		// number of animations || LOOP : || string name of animation || one texure offset value for animation x || (<- and the y) || one sizex for texRect || one sizey for texRect || number of frames in animation || startx || starty || pitch || ENDLOOP
		int numAnims;
		iFile >> numAnims;
		
		size_t currentNumAnims = m_texFramesRight.size();
		for (size_t i = currentNumAnims; i < (size_t)numAnims + currentNumAnims; i++)
		{
			std::string animName, direction;
			int frameOffX, frameOffY;
			int frameSizeX, frameSizeY;
			int numFrames;
			int startX, startY;
			int pitch;
			iFile >> animName >> direction >> frameOffX >> frameOffY >> frameSizeX >> frameSizeY >> numFrames >> startX >> startY >> pitch;

			int rows = std::max((numFrames / pitch), 1);
			int cols = pitch;
			
			m_frameOffset[animName] = { (float)frameOffX, (float)frameOffY };
			
			if (direction == "Right")
			{
				m_texFramesRight[animName] = std::vector<sf::IntRect>{};
				m_texFramesRight[animName].clear();
				m_texFramesRight[animName].reserve(numFrames);
				for (size_t j = 0; j < (size_t)(rows); j++)
				{
					for (size_t k = 0; k < numFrames; k++)
					{

						m_texFramesRight[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
					}
				}

				if (m_anim == nullptr)
				{
					m_anim = &m_texFramesRight[animName];
					m_animName = animName;
				}
			}
			else if (direction == "Left")
			{
				m_texFramesLeft[animName] = std::vector<sf::IntRect>{};
				m_texFramesLeft[animName].clear();
				m_texFramesLeft[animName].reserve(numFrames);
				for (size_t j = 0; j < (size_t)(rows); j++)
				{
					for (size_t k = 0; k < numFrames; k++)
					{

						m_texFramesLeft[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
					}
				}

				if (m_anim == nullptr)
				{
					m_anim = &m_texFramesLeft[animName];
					m_animName = animName;
				}
			}
			else
			{
				m_texFramesUni[animName] = std::vector<sf::IntRect>{};
				m_texFramesUni[animName].clear();
				m_texFramesUni[animName].reserve(numFrames);
				for (size_t j = 0; j < (size_t)(rows); j++)
				{
					for (size_t k = 0; k < numFrames; k++)
					{

						m_texFramesUni[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
					}
				}

				if (m_anim == nullptr)
				{
					m_anim = &m_texFramesUni[animName];
					m_animName = animName;
				}
			}

			// one animation completed
		}
		// all animations completed

		iFile.close();
	}
}

void DrawableObj::initializeAsTile(sf::IntRect rect_, Cfg::Textures tex_, sf::Vector2f pos_)
{
	m_texture = tex_;
	m_frameOffset["Tile"] = { 0.f,0.f };
	m_texFramesUni["Tile"] = std::vector<sf::IntRect>{};
	m_texFramesRight["Tile"] = std::vector<sf::IntRect>{};
	m_texFramesLeft["Tile"] = std::vector<sf::IntRect>{};
	m_texFramesUni["Tile"].clear();
	m_currentFrame = 0;
	m_animName = "Tile";
	m_uniDirectional = true;

	GObj::initialize((sf::Vector2f)rect_.size, pos_);
	this->m_frameDelays["Tile"] = 0.f;
	this->m_loopDelays["Tile"] = 0.f;
	this->m_startDelays["Tile"] = 0.f;
	this->m_texFramesUni["Tile"].push_back(rect_);
	m_anim = &m_texFramesUni["Tile"];
}

DrawableObj::DrawableObj()
	: GObj{}
{
	m_texFramesRight.clear();
	m_frameOffset.clear();
	m_startDelays.clear();
	m_loopDelays.clear();
	m_frameDelays.clear();
}

DrawableObj::~DrawableObj()
{

}

DrawableObj::DrawableObj(const DrawableObj& o)
	: GObj{}
{
	m_texFramesUni.clear();
	m_texFramesLeft.clear();
	m_texFramesRight.clear();
	m_frameOffset.clear();
	m_startDelays.clear();
	m_loopDelays.clear();
	m_frameDelays.clear();

	if (o.m_animName == "Tile")
	{
		this->initializeAsTile(o.m_texFramesUni.at(o.m_animName).at(o.m_currentFrame), o.m_texture, o.GetPosition());
		m_frameOffset["Tile"] = o.m_frameOffset.at("Tile");
	}
	else
	{
		GObj::initialize(o.GetSize(), o.GetPosition(), o.GetVelocity());
		m_frameOffset[o.m_animName] = o.m_frameOffset.at(o.m_animName);

	}
}

DrawableObj& DrawableObj::operator=(const DrawableObj& o)
{

	if (o.m_animName == "Tile")
	{
		this->initializeAsTile(o.m_texFramesUni.at(o.m_animName).at(o.m_currentFrame), o.m_texture, o.GetPosition());
		m_frameOffset["Tile"] = o.m_frameOffset.at("Tile");

	}
	else
	{
		GObj::initialize(o.GetSize(), o.GetPosition(), o.GetVelocity());
		m_frameOffset[o.m_animName] = o.m_frameOffset.at(o.m_animName);

	}
	return *this;
}

void DrawableObj::update(float dt_)
{
	// process input


	// update direction and m_anim 
	if (!m_uniDirectional)
	{
		//may switch
		if (m_facingRight)
		{
			if (m_anim != &m_texFramesRight[m_animName])
				m_anim = &m_texFramesRight[m_animName];
		}
		else
		{
			if (m_anim != &m_texFramesLeft[m_animName])
				m_anim = &m_texFramesLeft[m_animName];
		}
	}
	else
	{
		if (m_anim != &m_texFramesUni[m_animName])
			m_anim = &m_texFramesUni[m_animName];

	}

	// if animated, animate here
	GObj::tick(dt_);
}

void DrawableObj::render(sf::RenderWindow& wnd_)
{
	sf::Sprite spr(Cfg::textures.get((int)m_texture));
	auto pos = GetPosition();
	auto& offset = m_frameOffset[m_animName];
	spr.setPosition({ pos.x - offset.x, pos.y - offset.y });
	if (m_uniDirectional)
	{
		spr.setTextureRect(m_texFramesUni[m_animName].at(m_currentFrame));
	}
	else
	{
		if (m_facingRight)
		{
			spr.setTextureRect(m_texFramesRight[m_animName].at(m_currentFrame));
		}
		else
		{
			spr.setTextureRect(m_texFramesLeft[m_animName].at(m_currentFrame));
		}
	}
	wnd_.draw(spr);
}

void DrawableObj::ChangeAnim(const std::string& animName)
{
	if (this->m_facingRight && !this->m_uniDirectional) {
		if (m_texFramesRight.find(animName) == m_texFramesRight.end())
		{
			std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
			return;
		}
		m_anim = &m_texFramesRight[animName];
		
	}
	else if (!this->m_facingRight && !this->m_uniDirectional) {
		if (m_texFramesLeft.find(animName) == m_texFramesLeft.end())
		{
			std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
			return;
		}
		m_anim = &m_texFramesLeft[animName];
	}
	else
	{
		if (m_texFramesUni.find(animName) == m_texFramesUni.end())
		{
			std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
			return;
		}
		m_anim = &m_texFramesUni[animName];
	}
	m_currentFrame = 0;
	m_animName = animName;
	if (m_animName == "Idle")
	{
		m_looping = true;
		m_loopWaits = true;
	}
	else if (m_animName == "Moving")
	{
		m_looping = true;
		m_loopWaits = false;
	}
	else if (m_animName == "StartedMoving")
	{
		m_looping = false;
		m_loopWaits = false;
	}
}

void DrawableObj::animate()
{
	if (this->m_playing)
	{
		if (m_currentFrame == m_anim->size() - 1)
		{
			if (this->m_looping)
			{
				m_currentFrame = 0;
			}
		}
		else {
			m_currentFrame++;

			if (m_currentFrame > m_anim->size() - 1)
			{
				if (m_looping)
				{
					m_currentFrame = 0;
				}
				else
				{
					m_currentFrame = m_anim->size() - 1;
				}
			}

		}
	}
}

void DrawableObj::SetSize(const sf::Vector2f& size_)
{
	getPositionRef() = size_;
}

void DrawableObj::AdjustPosition(const sf::Vector2f& amt_)
{
	getPositionRef() += amt_;
}

void DrawableObj::SetPosition(const sf::Vector2f& pos_)
{
	getPositionRef() = pos_;
}

void DrawableObj::AdjustVelocity(const sf::Vector2f& amt_)
{
	getVelocityRef() += amt_;
}

void DrawableObj::SetVelocity(const sf::Vector2f& vel_)
{
	getVelocityRef() = vel_;
}

sf::Vector2f DrawableObj::getTexRectSize()
{
	if (m_animName == "None") 
	{
		std::cout << "Tried to get a texRectSize from m_texFramesRight without any anims added, nor frames to get the size of!  obj id " << this->ID() << std::endl;
		return sf::Vector2f(0, 0); 
	}
	return (sf::Vector2f)m_anim->at(m_currentFrame).size;
}

Cfg::Textures DrawableObj::getTextureID()
{
	return m_texture;
}

sf::Vector2f DrawableObj::getTexRectPos()
{
	if (m_anim == nullptr) { return sf::Vector2f(0, 0); }
	return (sf::Vector2f)m_anim->at(m_currentFrame).position;
}

void DrawableObj::setFrameOffset(std::string animName_, sf::Vector2f offset_)
{
	m_frameOffset[animName_] = offset_;
}

sf::Vector2f DrawableObj::getFrameOffset()
{
	return m_frameOffset[m_animName];
}
