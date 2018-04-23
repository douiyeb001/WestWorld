#include "GamePlayState.h"

CGamePlayState CGamePlayState::m_PlayState;

//! Default constructor
CGamePlayState::CGamePlayState()
{
}

//! Default destructor
CGamePlayState::~CGamePlayState()
{

}

CGamePlayState* CGamePlayState::Instance()
{
	return (&m_PlayState);
}

//! Keyboard event for state, main keyboard events
//! passed down by Game manager
void CGamePlayState::KeyboardEvent(CGameManager * pManager)
{
	// go to menu screen mode...
	//if (pManager->getKey(irr::KEY_ESCAPE)) pManager->getDevice()->closeDevice();

}

//! Mouse event handler passed down by CGameManager
void CGamePlayState::MouseEvent(CGameManager* pManager)
{
	// left mouse pressed,
	//if (pManager->getMouse() == EMIE_LMOUSE_PRESSED_DOWN)
	{
		// code here
	}
	// right mouse pressed,
//	if (pManager->getMouse() == EMIE_RMOUSE_PRESSED_DOWN)
	{
		// code here
	}

}
//! Initialisation, loads data required for state. Generic game play
//! initialisation performed here, level specific initialisation should
//! be performed by the sub-classed level
void CGamePlayState::Init(CGameManager* pManager)
{
}

//! Update, moves and renders screen. Generic game play updates performed here,
//! level specific updates should be performed by the sub-classed level.
void CGamePlayState::Update(CGameManager * pManager)
{
}

//! Clear, generic tidy up here, level specific house keeping should be
//! performed by the level specific subclass. Resources that have been
//! initialised should be destroyed also.
void CGamePlayState::Clear(CGameManager* pManager)
{

}

//! Displays Renderer, FPS and poly count on the screen
void CGamePlayState::DisplayFPS(CGameManager* pManager)
{

}

//! Loads the specified Quake MD3 level and performs general
//! map initialisation
void CGamePlayState::LoadMap(CGameManager* pManager, const c8 *map)
{
}
