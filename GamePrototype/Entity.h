#pragma once
class Player;
class Map;

class Entity
{
public:

	Entity(Point2f pos);
	~Entity();

	void Draw()const;
	void Update(Player& player, Map& map ,Entity& entity, float elapsedSec);

	Circlef GetEntityCircle();

	static int m_EntitySaved;
private:
	enum class State
	{
		idle, attract
	};

	State m_State;

	Point2f m_EntityPos;
	Ellipsef m_HitBoxGood;
	Ellipsef m_HitBoxBad;

	float m_Speed;
};


