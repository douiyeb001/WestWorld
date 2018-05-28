#include "PauseManager.h"
#include "MenuState.h"
#include "TestLevelState.h"

float originalPosX;
float originalPosY;

PauseManager::PauseManager(IVideoDriver* driver, IGUIEnvironment* gui)
{
	const float screenWidth = driver->getScreenSize().Width;
	const float screenHeight = driver->getScreenSize().Height;
	menuScreen = new Sprite(driver);
	menuScreen->texture = driver->getTexture("media/UI/StartMenu.png");
	menuScreen->scale = vector2d<f32>(.1, .1);
	//gui->addImage(menuScreen->texture,vector2d<s32>(0,0));
	originalPosX = screenWidth / 2;
	originalPosY = screenHeight / 2;
	
	menuScreen->position.X = originalPosX;
	menuScreen->position.Y = originalPosY;
	//test->setImage(menuScreen->texture);
	isPaused = false;
	//MouseIndicator = new Sprite(driver);
	menuScreen->draw();
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

bool PauseManager::isGamePaused() {
	return isPaused;
}

void PauseManager::RestartLevel(CGameManager* pManager) {
	
	pManager->ChangeState(TestLevelState::Instance());
}

void PauseManager::GoToStartMenu(CGameManager* pManager) {
	pManager->ChangeState(MenuState::Instance());
}

 void PauseManager::ExitGame(CGameManager* pManager) {
	pManager->getDevice()->closeDevice();
}

