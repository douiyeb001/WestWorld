#pragma once
#include <irrlicht.h>
#include "GameStates.h"
#include "Sprite.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

enum pauseStateID {
	RESUME = 0,
	RESTART = 1,
	MENU = 2,
	EXIT = 3
};

class PauseManager
{
public:
	PauseManager(IVideoDriver* driver, IGUIEnvironment* gui);
	~PauseManager();
	void TogglePause();
	void KeyboardEvent(CGameManager* pManager);
	void RestartLevel(CGameManager* pManager);
	void GoToStartMenu(CGameManager* pManager);
	void ExitGame(CGameManager* pManager);
	void Draw();
	Sprite* MouseIndicator;
	bool isGamePaused();
private:
	Sprite* menuScreen;
	int currentPauseId = 0;
	bool isPaused;
	
};

