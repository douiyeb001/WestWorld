#ifndef GAME_H
#define GAME_H

#include <irrlicht.h>
#include "GameManager.h"

using namespace irr;

//! Main entry point to game
class CGame
{
public:

	CGame();

	bool run();

private:
	CGameManager  m_GameManager;
};
#endif

