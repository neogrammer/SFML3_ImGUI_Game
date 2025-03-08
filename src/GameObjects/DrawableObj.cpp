#include "DrawableObj.h"
#include <iostream>
#include <fstream>
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
		
		size_t currentNumAnims = m_texFrames.size();
		for (size_t i = currentNumAnims; i < (size_t)numAnims + currentNumAnims; i++)
		{
			std::string animName;
			int frameOffX, frameOffY;
			int frameSizeX, frameSizeY;
			int numFrames;
			int startX, startY;
			int pitch;
			iFile >> animName >> frameOffX >> frameOffY >> frameSizeX >> frameSizeY >> numFrames >> startX >> startY >> pitch;

			int rows = (numFrames / pitch) + 1;
			int cols = pitch;
			m_frameOffset[animName] = { (float)frameOffX, (float)frameOffY };
			m_texFrames[animName] = std::vector<sf::IntRect>{};
			m_texFrames[animName].clear();
			m_texFrames[animName].reserve(numFrames);
			for (size_t j = 0; j < (size_t)(rows); j++)
			{
				for (size_t k = 0; k < numFrames; k++)
				{
					
					m_texFrames[animName].emplace_back(sf::IntRect{ {startX + (int)k * (int)frameSizeX,startY + (int)j * (int)frameSizeY},{(int)frameSizeX,(int)frameSizeY} });
				}
			}

			if (m_anim == nullptr)
			{
				m_anim = &m_texFrames[animName];
				m_animName = animName;
			}

			// one animation completed
		}
		// all animations completed

		iFile.close();
	}
}

void DrawableObj::initializeAsTile(sf::IntRect rect_, Cfg::Textures tex_, sf::Vector2f pos_)
{
	GObj::initialize((sf::Vector2f)rect_.size, pos_);
	m_texture = tex_;
	m_frameOffset["Tile"] = { 0.f,0.f };
	m_texFrames["Tile"] = std::vector<sf::IntRect>{};
	m_texFrames["Tile"].clear();
	m_texFrames["Tile"].push_back(rect_);
	m_anim = &m_texFrames["Tile"];
	m_currentFrame = 0;
	m_animName = "Tile";
}

DrawableObj::DrawableObj()
	: GObj{}
{
	m_texFrames.clear();
	m_frameOffset.clear();
}

DrawableObj::~DrawableObj()
{

}

DrawableObj::DrawableObj(const DrawableObj& o)
	: GObj{}
{

	GObj::initialize(o.GetSize(), o.GetPosition(), o.GetVelocity());
	if (o.m_animName == "Tile")
	{
		this->m_texFrames["Tile"] = std::vector<sf::IntRect>{};
		this->m_texFrames["Tile"].clear();
		for (int i = 0; i < o.m_texFrames.at("Tile").size(); i++)
		{
			this->m_texFrames["Tile"].push_back(o.m_texFrames.at("Tile")[i]);
		}
	}
}

DrawableObj& DrawableObj::operator=(const DrawableObj& o)
{

	GObj::initialize(o.GetSize(), o.GetPosition(), o.GetVelocity());
	if (o.m_animName == "Tile")
	{
		this->m_texFrames["Tile"] = std::vector<sf::IntRect>{};
		this->m_texFrames["Tile"].clear();
		for (int i = 0; i < o.m_texFrames.at("Tile").size(); i++)
		{
			this->m_texFrames["Tile"].push_back(o.m_texFrames.at("Tile")[i]);
		}
	}
	return *this;
}

void DrawableObj::update(float dt_)
{
	// if animated, animate here
	GObj::tick(dt_);
}

void DrawableObj::render(sf::RenderWindow& wnd_)
{
	sf::Sprite spr(Cfg::textures.get((int)m_texture));
	auto pos = GetPosition();
	auto offset = m_frameOffset[m_animName];
	spr.setPosition({ pos.x - offset.x, pos.y - offset.y });
	spr.setTextureRect((*m_anim).at(m_currentFrame));

	wnd_.draw(spr);
}

void DrawableObj::ChangeAnim(const std::string& animName)
{
	if (m_texFrames.find(animName) == m_texFrames.end())
	{
		std::cout << "Unable to find animation : " << animName << " in the texFrames of Object ID " << this->ID() << std::endl;
		return;
	}
	m_anim = &m_texFrames[animName];
	m_animName = animName;
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
		std::cout << "Tried to get a texRectSize from m_texFrames without any anims added, nor frames to get the size of!  obj id " << this->ID() << std::endl;
		return sf::Vector2f(0, 0); 
	}
	return (sf::Vector2f)m_texFrames.at(m_animName).at(m_currentFrame).size;
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
