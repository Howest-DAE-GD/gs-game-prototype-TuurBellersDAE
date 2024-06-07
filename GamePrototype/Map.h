#pragma once
class Entity;
class Player;

class Map
{
public:
	Map();
	~Map();

	void Draw()const;
	void Update(float elapsedSec);

	void HandleCollision(Player& player, Entity& entity);

	bool IsInGreenZone(Entity& entity) const;
	bool IsInRedZone(Entity& entity) const;
	Circlef GetRedZone()const;

private:
	Circlef m_GreenZone;
	Circlef m_RedZone;


};

