#pragma once
class Player;
class Map;
class Enemy;

class Entity
{
public:

	Entity(Point2f pos);
	~Entity();

	void Draw()const;
	void Update(Player& player, Map& map ,Entity& entity, float elapsedSec);

	void SpawnEnemy(float elapsedSec);

	Circlef GetEntityCircle();
	bool IsSecured();
	bool IsAbducted();

	static int m_EntitySaved;
private:
	enum class State
	{
		idle, attracted, secured, abducted
	};

	State m_State;

	Point2f m_EntityPos;
	Ellipsef m_HitBox;

	float m_Speed;

	Enemy* m_Enemy;
	float m_TimeIdx;
	bool m_EnemySpawned;
};


