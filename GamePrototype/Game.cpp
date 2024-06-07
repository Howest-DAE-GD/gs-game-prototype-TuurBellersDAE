#include "pch.h"
#include "Game.h"

Game::Game(const Window& window) : BaseGame(window)
{
	Initialize();
	m_LastSpawnTime = std::chrono::steady_clock::now();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_GameState = GameState::menu;

	m_IntroTxt = new Texture("intro.png");

	m_SavedStat = new Texture(std::to_string(Entity::GetEntitySave()), "font.ttf", 100, Color4f{ 0,1,0,1 });
	m_LostStat = new Texture(std::to_string(Entity::GetEntityLost()), "font.ttf", 100, Color4f{ 1,0,0,1 });

	m_SpawnTimer = 4;

	// Clear the existing entities
	for (Entity* entity : m_Entity)
	{
		delete entity;
	}

	m_Entity.clear();
}

void Game::Cleanup( )
{
	for (Entity* entity : m_Entity)
	{
		delete entity;
	}

	m_Entity.clear();
	m_SavedStat = nullptr;
	delete m_SavedStat;
	m_LostStat = nullptr;
	delete m_LostStat;
}

void Game::Update( float elapsedSec )
{
	switch (m_GameState)
	{
	case GameState::menu:
		break;
	case GameState::active:
		m_Player.Update(elapsedSec);

		SpawnEntity();

		for (int i = 0; i < m_Entity.size(); i++)
		{
			if (m_Entity[i] != nullptr)
			{
				if (m_Entity[i]->IsAbducted() or m_Entity[i]->IsSecured())
				{
					m_Entity[i] = nullptr;
					delete m_Entity[i];
				}
			}
		}

		for (int i = 0; i < m_Entity.size(); i++)
		{
			if (m_Entity[i] != nullptr)
			{
				m_Entity[i]->Update(m_Player, m_Map, *m_Entity[i], elapsedSec);
			}
		}

		break;
	}
	m_SavedStat = new Texture(std::to_string(Entity::GetEntitySave()), "font.ttf", 40, Color4f{ 0,1,0,1 });
	m_LostStat = new Texture(std::to_string(Entity::GetEntityLost()), "font.ttf", 40, Color4f{ 1,0,0,1 });
	
}

void Game::Draw( ) const
{
	ClearBackground( );

	switch (m_GameState)
	{
	case GameState::menu:
		m_IntroTxt->Draw(Point2f{ 0, 0 },
			Rectf{ 0,0,m_IntroTxt->GetWidth(),m_IntroTxt->GetHeight() });
		break;
	case GameState::active:
		m_Map.Draw();
		m_Player.Draw();

		for (int i = 0; i < m_Entity.size(); i++)
		{
			if (m_Entity[i] != nullptr)
			{
				m_Entity[i]->Draw();
			}
		}
		m_SavedStat->Draw(Point2f{ 15,650 }, Rectf{ 0,0,m_SavedStat->GetWidth(),m_SavedStat->GetHeight() });
		m_LostStat->Draw(Point2f{ 15,600 }, Rectf{ 0,0,m_LostStat->GetWidth(),m_LostStat->GetHeight() });
		break;
	}

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_ESCAPE:
		BaseGame::~BaseGame();
		break;
	case SDLK_p:
		m_GameState = GameState::active;
		break;
	}

	switch (m_GameState)
	{
	case GameState::menu:
		break;
	case GameState::active:
		m_Player.ProcessKeyDownEvent(e);
		break;
	}
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_Player.ProcessKeyUpEvent(e);
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	switch (m_GameState)
	{
	case GameState::menu:
		break;
	case GameState::active:
		m_Player.ProcessMouseMotionEvent(e);
		break;
	}
	
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::SpawnEntity()
{
	// Check if it's time to spawn a new entity
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_LastSpawnTime).count();

	if (elapsedSeconds >= m_SpawnTimer)
	{
		if (m_SpawnTimer > 1)
		{
			m_SpawnTimer -= 0.1f;
		}
		else
		{
			m_SpawnTimer = 1;
		}
		// Spawn a new entity
		float posX = static_cast<float>(rand() % 1300 + 50);
		float posY = static_cast<float>(rand() % 600 + 50);

		m_Entity.push_back(new Entity(Point2f{ posX, posY }));

		// Update the last spawn time
		m_LastSpawnTime = currentTime;
	}
}
