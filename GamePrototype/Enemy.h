#pragma once
class Player;
class Map;
class Entity;

class Enemy
{
public:

	Enemy(Point2f pos);
	~Enemy();

	void Draw()const;
	void Update(Player& player, Map& map, Entity& entity, float elapsedSec);

	Circlef GetEnemyCircle();
	Circlef GetAttractionZone();
	Point2f GetPos();

private:
	enum class State
	{
		hunting, abducting
	};

	State m_State;

	Point2f m_EnemyPos;
	Ellipsef m_HitBox;
	Ellipsef m_AttractionZone;

	float m_Speed;
};

