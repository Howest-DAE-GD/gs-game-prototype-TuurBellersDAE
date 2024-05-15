#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <cmath>
#include <iostream>

Player::Player() :
	m_PlayerPos{700,350},
	m_Velocity{0,0},
	m_Speed{150},
	m_Acceleration{250},
	m_MaxSpeed{400},
	m_Resistance{1},
	m_State{State::cruising}
{
	m_HitBox.center = m_PlayerPos;
	m_HitBox.radiusX = 15;
	m_HitBox.radiusY = 15;

	m_AttractionZone.center = m_PlayerPos;
	m_AttractionZone.radiusX = 100;
	m_AttractionZone.radiusY = 100;
}

Player::~Player()
{
}

void Player::Draw() const
{
	utils::SetColor(Color4f{ 0,0,1,1 });
	utils::FillEllipse(m_HitBox);
	utils::SetColor(Color4f{ 0,1,0,1 });
	utils::DrawEllipse(m_AttractionZone);
}

void Player::Update(float elapsedSec)
{

	float dx = m_MousePos.x - m_PlayerPos.x;
	float dy = m_MousePos.y - m_PlayerPos.y;

	float distance = std::sqrt(dx * dx + dy * dy);

	if (distance != 0)
	{
		dx = dx / distance;
		dy = dy / distance;
	}

	if (m_State == State::accelerating)
	{
		m_Speed += m_Acceleration * elapsedSec;
		if (m_Speed >= m_MaxSpeed)
		{
			m_Speed = m_MaxSpeed;
			m_State = State::maxspeed;
		}
	}
	else if (m_State == State::maxspeed)
	{
		m_Speed = m_MaxSpeed;
	}
	else
	{
		m_Speed = 150;
	}

	m_PlayerPos.x += dx * m_Speed * m_Resistance * elapsedSec;
	m_PlayerPos.y += dy * m_Speed * m_Resistance * elapsedSec;

	m_HitBox.center = m_PlayerPos;
	m_AttractionZone.center = m_PlayerPos;
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		break;
	case SDLK_RIGHT:
		break;
	case SDLK_DOWN:
		break;
	case SDLK_UP:
		break;
	case SDLK_SPACE:
		if (m_State == State::cruising)
		{
			m_State = State::accelerating;
		}
		break;
	}
}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		break;
	case SDLK_RIGHT:
		break;
	case SDLK_DOWN:
		break;
	case SDLK_UP:
		break;
	case SDLK_SPACE:
		m_State = State::cruising;
		break;
	}
}

void Player::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePos.x = e.x;
	m_MousePos.y = e.y;
}

Ellipsef Player::GetAttractionZone() const
{
	return m_AttractionZone;
}

Ellipsef Player::GetHitBox() const
{
	return m_HitBox;
}

Point2f Player::GetPos() const
{
	return m_PlayerPos;
}
