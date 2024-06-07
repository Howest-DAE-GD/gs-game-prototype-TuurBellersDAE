#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include <chrono>
#include <vector>
#include "Texture.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void SpawnEntity();

	enum class GameState
	{
		menu,active
	};

	GameState m_GameState;
	Texture* m_IntroTxt;
	Texture* m_SavedStat;
	Texture* m_LostStat;

	std::chrono::steady_clock::time_point m_LastSpawnTime;
	std::vector<Entity*> m_Entity;
	Map m_Map;
	Player m_Player;

	float m_SpawnTimer;

	//Entity m_Entity;
};