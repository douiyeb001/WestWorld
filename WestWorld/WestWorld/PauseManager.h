#pragma once
#include <irrlicht.h>
#include "GameStates.h"
#include "Sprite.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

class PauseManager
{
public:
	PauseManager(IVideoDriver* driver, IGUIEnvironment* gui);
	void TogglePause();
	void RestartLevel(CGameManager* pManager);
	void GoToStartMenu(CGameManager* pManager);
	void ExitGame(CGameManager* pManager);
	void Draw();
	Sprite* MouseIndicator;
	bool isGamePaused();
private:
	Sprite* menuScreen;
	bool isPaused = false;
	~PauseManager();
};

