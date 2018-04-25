#include "Game.h"


CGame::CGame()
{
}

//! Main game loop
bool CGame::run()
{
	// Name of game, displayed in window if windowed
	m_GameManager.getDevice()->setWindowCaption(L"WestWorld");

	// Keep running game loop if device exists
	while (m_GameManager.getDevice()->run())
	{
		if (m_GameManager.getDevice()->isWindowActive())
		{
			m_GameManager.Update();
		}
	}

	m_GameManager.getDevice()->drop();


	return 0;
}



