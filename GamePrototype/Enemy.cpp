#include "pch.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include <cmath>
#include "utils.h"

Enemy::Enemy(Point2f pos) :
	m_EnemyPos{ pos },
	m_Speed{ 125 },
	m_State{ State::hunting }
{
	m_HitBox.center = m_EnemyPos;
	m_HitBox.radiusX = 5;
	m_HitBox.radiusY = 5;

	m_AttractionZone.center = m_EnemyPos;
	m_AttractionZone.radiusX = 20;
	m_AttractionZone.radiusY = 20;
}

Enemy::~Enemy()
{
}

void Enemy::Draw() const
{
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::FillEllipse(m_HitBox);
	utils::SetColor(Color4f{ 1,1,0,1 });
	utils::DrawEllipse(m_AttractionZone);
}

void Enemy::Update(Player& player, Map& map, Entity& entity, float elapsedSec)
{
	float dx{};
	float dy{};
	float distance{};

	if (utils::IsOverlapping(Circlef{ m_EnemyPos,m_AttractionZone.radiusX },entity.GetEntityCircle()))
	{
		m_State = State::abducting;
	}
	else
	{
		m_State = State::hunting;
	}



	switch (m_State)
	{
	case State::hunting:
		dx = entity.GetEntityCircle().center.x - m_EnemyPos.x;
		dy = entity.GetEntityCircle().center.y - m_EnemyPos.y;

		distance = std::sqrt(dx * dx + dy * dy);

		if (distance != 0)
		{
			dx = dx / distance;
			dy = dy / distance;
		}
		break;
	case State::abducting:
		dx = map.GetRedZone().center.x - m_EnemyPos.x;
		dy = map.GetRedZone().center.y - m_EnemyPos.y;

		distance = std::sqrt(dx * dx + dy * dy);

		if (distance != 0)
		{
			dx = dx / distance;
			dy = dy / distance;
		}
		break;
	}

	m_EnemyPos.x += dx * m_Speed * elapsedSec;
	m_EnemyPos.y += dy * m_Speed * elapsedSec;

	m_HitBox.center = m_EnemyPos;
	m_AttractionZone.center = m_EnemyPos;
}

Circlef Enemy::GetEnemyCircle()
{
	return Circlef{ m_EnemyPos,m_HitBox.radiusX };
}

Circlef Enemy::GetAttractionZone()
{
	return Circlef{ m_EnemyPos,m_AttractionZone.radiusX };
}

Point2f Enemy::GetPos()
{
	return m_EnemyPos;
}
