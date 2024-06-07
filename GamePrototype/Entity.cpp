#include "pch.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "utils.h"
#include "Enemy.h"
#include <cmath>
#include <iostream>
#include <chrono>

int Entity::m_EntitySaved = 0;

Entity::Entity(Point2f pos) :
	m_EntityPos{pos},
	m_Speed{125},
	m_State{State::idle},
	m_TimeIdx{0},
	m_EnemySpawned{false}
{
	m_Enemy = nullptr;
	m_HitBox.center = m_EntityPos;
	m_HitBox.radiusX = 5;
	m_HitBox.radiusY = 5;
}

Entity::~Entity()
{
}

void Entity::Draw() const
{
	utils::SetColor(Color4f{ 0,1,1,1 });
	utils::FillEllipse(m_HitBox);
	if (m_Enemy != nullptr)
	{
		m_Enemy->Draw();
	}
}

void Entity::Update(Player& player, Map& map, Entity& entity, float elapsedSec) //make it so they colide with eachother and with the player too
{
	SpawnEnemy(elapsedSec);

	if (m_Enemy != nullptr)
	{
		m_Enemy->Update(player,map,*this,elapsedSec);
	}
	float dx{};
	float dy{};
	
	float distance = std::sqrt(dx * dx + dy * dy);

	if (utils::IsOverlapping(Circlef{ m_EntityPos,m_HitBox.radiusX }, Circlef{ player.GetPos(),player.GetAttractionZone().radiusX }))
	{
		dx = player.GetPos().x - m_EntityPos.x;
		dy = player.GetPos().y - m_EntityPos.y;

		distance = std::sqrt(dx * dx + dy * dy);

		if (distance != 0)
		{
			dx = dx / distance;
			dy = dy / distance;
		}
	}
	else if (m_Enemy != nullptr)
	{
		if (utils::IsOverlapping(Circlef{ m_EntityPos,m_HitBox.radiusX }, Circlef{ m_Enemy->GetAttractionZone().center,m_Enemy->GetAttractionZone().radius + 10 }))
		{
			dx = m_Enemy->GetPos().x - m_EntityPos.x;
			dy = m_Enemy->GetPos().y - m_EntityPos.y;

			distance = std::sqrt(dx * dx + dy * dy);

			if (distance != 0)
			{
				dx = dx / distance;
				dy = dy / distance;
			}
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
		m_State = State::secured;

		m_Enemy = nullptr;
		delete m_Enemy;
		return;
	}
	if (map.IsInRedZone(*this))
	{
		++m_EntitySaved;
		m_State = State::abducted;

		m_Enemy = nullptr;
		delete m_Enemy;
		return;
	}

	

	m_EntityPos.x += dx * m_Speed * elapsedSec;
	m_EntityPos.y += dy * m_Speed * elapsedSec;

	m_HitBox.center = m_EntityPos;
}

void Entity::SpawnEnemy(float elapsedSec)
{
	// Check if it's time to spawn a new entity
	m_TimeIdx += elapsedSec;
	
	if (m_TimeIdx >= 5 and !m_EnemySpawned)
	{
		float distance = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (300)));
		float angle = static_cast<float>(rand());
		// Spawn a new entity
		float posX = m_EntityPos.x + distance * cos (angle);
		float posY = m_EntityPos.y + distance * sin(angle);
		m_EnemySpawned = true;
		m_Enemy = new Enemy(Point2f{ posX,posY });
	}
}

Circlef Entity::GetEntityCircle()
{
	return Circlef{m_EntityPos,m_HitBox.radiusX};
}

bool Entity::IsSecured()
{
	if (m_State == State::secured)
	{
		return true;
	}

	return false;
}

bool Entity::IsAbducted()
{
	if (m_State == State::abducted)
	{
		return true;
	}

	return false;
}
