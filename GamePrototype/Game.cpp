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
	for (int i = 0; i < 10; i++)
	{
		m_Entity[i] = new Entity(Point2f{ 0, 0 });
	}
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_Player.Update(elapsedSec);

	// Check if 5 seconds have elapsed since the last spawn
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_LastSpawnTime).count();

	if (elapsedSeconds >= 5)
	{
		// Spawn the entities
		SpawnEntity();

		// Update the last spawn time
		m_LastSpawnTime = currentTime;
	}

	for (int i = 0; i < 10; i++)
	{
		
			m_Entity[i]->Update(m_Player, m_Map, elapsedSec);
		
	}
	
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_Map.Draw();
	m_Player.Draw();

	for (int i = 0; i < 10; i++)
	{
		if (m_Entity[i] != nullptr)
		{
			m_Entity[i]->Draw();
		}
	}

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player.ProcessKeyDownEvent(e);
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
	m_Player.ProcessMouseMotionEvent(e);
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
	for (int i = 0; i < 10; i++)
	{
		float posX = static_cast<float>(rand() % 1300 + 50);
		float posY = static_cast<float>(rand() % 600 + 50);

		m_Entity[i] = new Entity(Point2f{ posX, posY });
	}
}
