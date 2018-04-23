#include "GamePlayState.h"

/// <summary>	State of the game play state m play. </summary>
CGamePlayState CGamePlayState::m_PlayState;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CGamePlayState::CGamePlayState()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CGamePlayState::~CGamePlayState()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the instance. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else a pointer to a CGamePlayState. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

CGamePlayState* CGamePlayState::Instance()
{
	return (&m_PlayState);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Keyboard event for state, main keyboard events passed down by Game manager </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGamePlayState::KeyboardEvent(CGameManager * pManager)
{
	// go to menu screen mode...
	//if (pManager->getKey(irr::KEY_ESCAPE)) pManager->getDevice()->closeDevice();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Mouse event handler passed down by CGameManager. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Initialisation, loads data required for state. Generic game play initialisation performed here, 
/// 			level specific initialisation should be performed by the sub-classed level </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGamePlayState::Init(CGameManager* pManager)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Update, moves and renders screen. Generic game play updates performed here, 
/// 		    level specific updates should be performed by the sub-classed level. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGamePlayState::Update(CGameManager * pManager)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	 Clear, generic tidy up here, level specific house keeping should be performed by the level specific subclass. 
/// 			 Resources that have been initialised should be destroyed also. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGamePlayState::Clear(CGameManager* pManager)
{

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Displays Renderer, FPS and poly count on the screen </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGamePlayState::DisplayFPS(CGameManager* pManager)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Loads the specified Quake MD3 level and performs general map initialisation </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
/// <param name="map">	   	The map. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGamePlayState::LoadMap(CGameManager* pManager, const c8 *map)
{
}
