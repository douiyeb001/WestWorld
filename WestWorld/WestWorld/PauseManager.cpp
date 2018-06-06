#include "PauseManager.h"
#include "MenuState.h"
#include "TestLevelState.h"

float originalPosX;
float originalPosY;

using namespace irr;
using namespace video;
using namespace gui;

PauseManager::PauseManager(IVideoDriver* driver, IGUIEnvironment* gui){
	const float screenWidth = driver->getScreenSize().Width;
	const float screenHeight = driver->getScreenSize().Height;
	menuScreen = new Sprite(driver);
	menuScreen->texture = driver->getTexture("media/UI/StartMenu.png");
	menuScreen->scale = vector2d<f32>(.1, .1);
	originalPosX = screenWidth / 2;
	originalPosY = screenHeight / 2;
	menuScreen->position.X = originalPosX;
	menuScreen->position.Y = originalPosY;
	isPaused = false;
}

PauseManager::~PauseManager()
{
}

void PauseManager::TogglePause() {
	isPaused = !isPaused;
}

void PauseManager::KeyboardEvent(CGameManager* pManager) {
	if ((pManager->GetKeyboard() == KEY_DOWN) && currentPauseId < 3) {
		currentPauseId++;
	}
	if ((pManager->GetKeyboard() == KEY_UP) && currentPauseId > 0) {
		currentPauseId--;
	}

	if (pManager->GetKeyboard() == KEY_RETURN) switch (pauseStateID(currentPauseId)) {
	case RESUME:
		TogglePause();
		break;
	case RESTART:
		RestartLevel(pManager);
		break;
	case MENU:
		GoToStartMenu(pManager);
		break;
	case EXIT:
		ExitGame(pManager);
		break;
	}
}


void PauseManager::Draw() {
//	menuScreen->draw();// this no work
}


//! returns if the current state of the game is paused or not
bool PauseManager::IsGamePaused() {
	return isPaused;
}

//! changes the state back to the TestLevelState
//! this is a restart of the level
void PauseManager::RestartLevel(CGameManager* pManager) {
	pManager->ChangeState(TestLevelState::Instance());
}

//! changes the state back to the MenuState
//! ChangeState will clean up the level
void PauseManager::GoToStartMenu(CGameManager* pManager) {
	pManager->ChangeState(MenuState::Instance());
}

//! closes the Irrlicht device which in turn closes the application
 void PauseManager::ExitGame(CGameManager* pManager) {
	pManager->getDevice()->closeDevice();
}

