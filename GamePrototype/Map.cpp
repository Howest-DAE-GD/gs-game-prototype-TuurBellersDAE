#include "pch.h"
#include "Map.h"
#include "utils.h"
#include "Entity.h"

Map::Map():
	m_GreenZone{ Point2f{1300,350}, 50 },
	m_RedZone{Point2f{100,350}, 50}
{
}

Map::~Map()
{
}

void Map::Draw() const
{
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::DrawEllipse(m_RedZone.center, m_RedZone.radius, m_RedZone.radius);
	utils::SetColor(Color4f{ 0,1,0,1 });
	utils::DrawEllipse(m_GreenZone.center, m_GreenZone.radius, m_GreenZone.radius);

}

void Map::Update(float elapsedSec)
{
}

void Map::HandleCollision(Player& player, Entity& entity)
{
}

bool Map::IsInGreenZone(Entity& entity) const
{
	if (utils::IsOverlapping(m_GreenZone, entity.GetEntityCircle()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::IsInRedZone(Entity& entity) const
{
	if (utils::IsOverlapping(m_RedZone, entity.GetEntityCircle()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Circlef Map::GetRedZone() const
{
	return m_RedZone;
}
