////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	Game.h
//
// summary:	Declares the game class
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include <irrlicht.h>
#include "GameManager.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

//! Main entry point to game
class CGame
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CGame();

	bool run();

private:
	/// <summary>	Manager for game. </summary>
	CGameManager  m_GameManager;
};
#endif

