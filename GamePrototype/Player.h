#pragma once
#include "Vector2f.h"


class Player
{
public:
	Player();
	~Player();

	void Draw()const;
	void Update(float elapsedSec);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);

	Ellipsef GetAttractionZone() const;
	Ellipsef GetHitBox() const;
	Point2f GetPos() const;

private:
	enum class State
	{
		cruising,accelerating, maxspeed
	};

	State m_State;

	Point2f m_PlayerPos;
	Point2f m_MousePos;

	Ellipsef m_HitBox;
	Ellipsef m_AttractionZone;

	Vector2f m_Velocity;
	float m_Speed;
	float m_Acceleration;
	float m_Stamina; ////////
	float m_MaxSpeed;
	float m_Resistance;


};

