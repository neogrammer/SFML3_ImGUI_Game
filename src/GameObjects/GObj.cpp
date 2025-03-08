#include "GObj.h"
#include <iostream>
size_t GObj::totalGameObjects = { 0 };

GObj::GObj(){ }

GObj::~GObj(){  }

void GObj::tick(float dt_)
{
	m_position += m_velocity * dt_;

	static bool moved = false;
	if (m_position != m_prevPosition)
	{
		moved = true;
	}
	else
	{
		moved = false;
	}

	if (moved)
	{
		m_prevMoveAmt = {m_position.x - m_prevPosition.x, m_position.y - m_prevPosition.y};
		m_prevPosition = m_position;
	}
}

void GObj::initialize(sf::Vector2f size_, sf::Vector2f pos_, sf::Vector2f vel_)
{
	m_size = size_;
	m_position = pos_;
	m_prevPosition = m_position;
	m_velocity = vel_;
	m_prevMoveAmt = { 0.f, 0.f };
}

void GObj::SetSize(const sf::Vector2f& size_)
{
	m_size = size_;
}

void GObj::AdjustPosition(const sf::Vector2f& amt_)
{
	m_position += amt_;
}

void GObj::SetPosition(const sf::Vector2f& pos_)
{
	m_position = pos_;
}

void GObj::AdjustVelocity(const sf::Vector2f& amt_)
{
	m_velocity += amt_;
}

void GObj::SetVelocity(const sf::Vector2f& vel_)
{
	m_velocity = vel_;
}

bool operator==(GObj& lhs_, GObj& rhs_)
{
	return (lhs_.m_id == rhs_.m_id);
}
