#include "pch.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "utils.h"
#include <cmath>
#include <iostream>

int Entity::m_EntitySaved = 0;

Entity::Entity(Point2f pos) :
	m_EntityPos{pos},
	m_Speed{125},
	m_State{State::idle}
{
	m_HitBoxGood.center = m_EntityPos;
	m_HitBoxGood.radiusX = 5;
	m_HitBoxGood.radiusY = 5;
	//m_EntitySaved = 0;
}

Entity::~Entity()
{
}

void Entity::Draw() const
{
	utils::SetColor(Color4f{ 0,1,1,1 });
	utils::FillEllipse(m_HitBoxGood);
}

void Entity::Update(Player& player, Map& map, Entity& entity, float elapsedSec) //make it so they colide with eachother and with the player too
{
	float dx = player.GetPos().x - m_EntityPos.x;
	float dy = player.GetPos().y - m_EntityPos.y;

	if (utils::IsOverlapping(Circlef{ m_EntityPos,m_HitBoxGood.radiusX }, Circlef{ player.GetPos(),player.GetAttractionZone().radiusX }))
	{
		

		float distance = std::sqrt(dx * dx + dy * dy);

		if (distance != 0)
		{
			dx = dx / distance;
			dy = dy / distance;
		}
	}
	else
	{
		dx = 0;
		dy = 0;
	}


	if (map.IsInGreenZone(*this))
	{
		++m_EntitySaved;

		delete this;
		return;
	}
	


	m_EntityPos.x += dx * m_Speed * elapsedSec;
	m_EntityPos.y += dy * m_Speed * elapsedSec;

	m_HitBoxGood.center = m_EntityPos;
}

Circlef Entity::GetEntityCircle()
{
	return Circlef{m_EntityPos,m_HitBoxGood.radiusX};
}
