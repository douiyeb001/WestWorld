#include "MenuState.h"
#include  "TestLevelState.h"

MenuState MenuState::m_MenuState;

MenuState::MenuState(){}

MenuState::~MenuState(){}

MenuState* MenuState::Instance() {
	return (&m_MenuState);
}

void MenuState::Init(CGameManager* pManager) {
	CGameState::Init(pManager);

	//Menu screen image setup
	float height = pManager->getDriver()->getScreenSize().Height;
	float width = pManager->getDriver()->getScreenSize().Width;

	pBackgroundImage = new UI(pManager->getDriver(), "media/UI/StartMenu.png");
	pMouseCursor = new UI(pManager->getDriver(), "media/UI/revolverIcon.png");

	m_pCamera = pManager->getSceneManager()->addCameraSceneNode(0, core::vector3df(0, 0, 10));

	ISceneNodeAnimator* anim = pManager->getSceneManager()->createFlyCircleAnimator(
		vector3df(0, 5, 0), 25.0f, 0.0002f);
	m_pCamera->addAnimator(anim);
	anim->drop();
	
	CGameState::FadeInOut(pManager);
}

void MenuState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	pBackgroundImage->Draw(pManager->getDriver());
	pMouseCursor->Draw(pManager->getDriver());
	DisplayMouse(pManager);
	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

void MenuState::Clear(CGameManager* pManager) {
	pManager->getSceneManager()->clear();
}

void MenuState::MouseEvent(CGameManager* pManager) {  }

void MenuState::KeyboardEvent(CGameManager* pManager) {

	if ((pManager->GetKeyboard() == KEY_DOWN) && currentMenuId < 2) currentMenuId++;
	if ((pManager->GetKeyboard() == KEY_UP) && currentMenuId > 0) currentMenuId--;
	
	if (pManager->GetKeyboard() == KEY_RETURN) switch (menuStateID(currentMenuId)) {
	case START:
			ChangeState(pManager, TestLevelState::Instance());
		break;
	case CONTROLS:
		break;
	case QUIT:
		pManager->getDevice()->closeDevice();
		break;
	}
}

void MenuState::DisplayMouse(CGameManager* pManager) {
	/*m_pCamera->setTarget(core::vector3df(0,5,0));
	pManager->getDriver()->draw2DImage(m_pLogoImage, core::position2d<s32>(800/2,10),core::rect<s32>(0,0,278,218),0,video::SColor(255,255,255,255),true);
	pManager->getDriver()->draw2DImage(m_pStartImage, core::position2d<s32>(800/3+80,650),core::rect<s32>(0,0,340,64),0,video::SColor(255,255,255,255),true);
	if(!m_bMouseMode) {
		m_MousePos = pManager->getDevice()->getCursorControl()->getPosition();
		pManager->getDriver()->draw2DImage(m_pMouseCursor, core::position2d<s32>(m_MousePos.X, m_MousePos.Y),
			core::rect<s32>(0,0,32,32), 0, video::SColor(255,255,255,255), true);
	}*/
}

void MenuState::MouseClicked(CGameManager* pManager) {  }

UI::UI(IVideoDriver* driver, char const* icon) {
	texture = driver->getTexture(icon);
}

void UI::Draw(IVideoDriver* driver) {
	driver->draw2DImage(texture,
		core::position2d<int>(20, 20),
		core::rect<int>(0, 0, texture->getSize().Width, texture->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw bar
}








