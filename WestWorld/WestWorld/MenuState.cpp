#include "MenuState.h"
#include  "TestLevelState.h"
#include "TutorialState.h"
#include <irrKlang-64bit-1.6.0/include/irrKlang.h>


irrklang::ISoundEngine* engine;
MenuState MenuState::m_MenuState;

MenuState::MenuState(){}

MenuState::~MenuState(){}


MenuState* MenuState::Instance() {
	return (&m_MenuState);
}

void MenuState::Init(CGameManager* pManager) {
	engine = pManager->GetSoundEngine();
	currentMenuId = 0;
	CGameState::Init(pManager);
	//Menu screen image setup
	float height = pManager->GetDriver()->getScreenSize().Height;
	float width = pManager->GetDriver()->getScreenSize().Width;
	backgroundSprite = new Sprite(pManager->GetDriver());
	backgroundSprite->texture = pManager->GetDriver()->getTexture("media/UI/StartMenu.png");
	backgroundSprite->position.X = pManager->GetDriver()->getScreenSize().Width / 2;
	backgroundSprite->position.Y = pManager->GetDriver()->getScreenSize().Height / 2;

	controlSchemeSprite = new Sprite(pManager->GetDriver());
	controlSchemeSprite->texture = pManager->GetDriver()->getTexture("media/UI/ControlScheme.png");
	controlSchemeSprite->position.X = width/2;
	controlSchemeSprite->position.Y = height/2;

	revolverSprite = new Sprite(pManager->GetDriver());
	revolverSprite->texture = pManager->GetDriver()->getTexture("media/UI/revolverIcon.png");
	revolverSprite->scale.X = .3;
	revolverSprite->scale.Y = .3;
	revolverSprite->position.X = 350;
	revolverSprite->position.Y = 150;

	/*m_pCamera = pManager->GetSceneManager()->addCameraSceneNode(0, core::vector3df(0, 0, 10));

	ISceneNodeAnimator* anim = pManager->GetSceneManager()->createFlyCircleAnimator(
		vector3df(0, 5, 0), 25.0f, 0.0002f);
	m_pCamera->addAnimator(anim);*/
	
	FadeInOut(pManager);
	engine->setSoundVolume(0.2);
	engine->play2D("media/Sound/Music/WesternInside.wav",true);
}

void MenuState::Update(CGameManager* pManager) {
	pManager->GetDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->GetSceneManager()->drawAll();

	backgroundSprite->draw();
	revolverSprite->draw();
	if (onControlScreen)
	controlSchemeSprite->draw();
//	pBackgroundImage->Draw(pManager->GetDriver());
//	pMouseCursor->Draw(pManager->GetDriver());
	DisplayMouse(pManager);
	pManager->GetGUIEnvironment()->drawAll();
	pManager->GetDriver()->endScene();
}

void MenuState::Clear(CGameManager* pManager) {
	engine->stopAllSounds();
	pManager->GetSceneManager()->clear();
	delete backgroundSprite;
	backgroundSprite = 0;
	delete revolverSprite;
	revolverSprite = 0;
	//delete[] ismgr;
}

void MenuState::MouseEvent(CGameManager* pManager) {  }

void MenuState::KeyboardEvent(CGameManager* pManager) {

	if ((pManager->GetKeyboard() == KEY_DOWN) && currentMenuId < 2) {
		currentMenuId++;
		if (onControlScreen) onControlScreen = false;
		revolverSprite->position.Y += 125;
	}
	if ((pManager->GetKeyboard() == KEY_UP) && currentMenuId > 0) {
		currentMenuId--;
		if (onControlScreen) onControlScreen = false;
		revolverSprite->position.Y -= 125;
	}
	
	if (pManager->GetKeyboard() == KEY_RETURN) switch (menuStateID(currentMenuId)) {
	case START:
			ChangeState(pManager, TutorialState::Instance());
		
		break;
	case CONTROLS:
		onControlScreen = true;
		break;
	case QUIT:
		pManager->getDevice()->closeDevice();
		break;
	}

	if(pManager->GetKeyboard() == KEY_ESCAPE) {
		if (onControlScreen) onControlScreen = false;
	}
	if (pManager->GetKeyboard() == KEY_F1)
	{
	//	ReinitializeState(pManager, MenuState::Instance());
		//delete[]	MenuState::Instance();
		Clear(pManager);
		Init(pManager);
		ReinitializeState(pManager, MenuState::Instance());
	}
}

void MenuState::DisplayMouse(CGameManager* pManager) {
	/*m_pCamera->setTarget(core::vector3df(0,5,0));
	pManager->GetDriver()->draw2DImage(m_pLogoImage, core::position2d<s32>(800/2,10),core::rect<s32>(0,0,278,218),0,video::SColor(255,255,255,255),true);
	pManager->GetDriver()->draw2DImage(m_pStartImage, core::position2d<s32>(800/3+80,650),core::rect<s32>(0,0,340,64),0,video::SColor(255,255,255,255),true);
	if(!m_bMouseMode) {
		m_MousePos = pManager->getDevice()->getCursorControl()->getPosition();
		pManager->GetDriver()->draw2DImage(m_pMouseCursor, core::position2d<s32>(m_MousePos.X, m_MousePos.Y),
			core::rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
	}*/
}

void MenuState::MouseClicked(CGameManager* pManager) {  }

//void MenuState::switchMousePos(int state) {
//	switch(state) {
//	case START:
//		revolverSprite->position.Y = 150;
//		
//		break;
//	case CONTROLS:
//		 Controls = 275
//		break;
//	case Quit:
//		// Quit = 400
//	}
//}







