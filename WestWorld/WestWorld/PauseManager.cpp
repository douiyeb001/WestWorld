#include "PauseManager.h"



PauseManager::PauseManager(IVideoDriver* driver, IGUIEnvironment* gui)
{
	const float screenWidth = driver->getScreenSize().Width;
	const float screenHeight = driver->getScreenSize().Height;
	menuScreen = new Sprite(driver);
	menuScreen->texture = driver->getTexture("media/UI/StartMenu.png");
	menuScreen->scale = vector2d<f32>(.1, .1);
	//gui->addImage(menuScreen->texture,vector2d<s32>(0,0));

	
	menuScreen->position.X = screenWidth / 2;
	menuScreen->position.Y = screenHeight / 2;
	//MouseIndicator = new Sprite(driver);

}

PauseManager::~PauseManager()
{
}

void PauseManager::TogglePause() {
	isPaused = !isPaused;
}

void PauseManager::Draw() {
//	if (!isPaused) return;

	menuScreen->draw();// this no work
	
}

bool PauseManager::isGamePaused() {
	return isPaused;
}



void PauseManager::RestartLevel(CGameManager* pManager) {  }

void PauseManager::GoToStartMenu(CGameManager* pManager) {  }

 void PauseManager::ExitGame(CGameManager* pManager) {
	pManager->getDevice()->closeDevice();
}

