#include "TestLevelState.h"

TestLevelState TestLevelState::m_TestLevelState;

TestLevelState::TestLevelState(){

}


TestLevelState::~TestLevelState(){

}

TestLevelState* TestLevelState::Instance(){
	return(&m_TestLevelState);
}

void TestLevelState::Init(CGameManager* pManager) {
	//m_titlePic = pManager->getDriver()->getTexture("media/fire.jpg");
	pManager->getSceneManager()->loadScene("scene/terrain.irr");
	cameraNode = pManager->getSceneManager()->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));
	pManager->SetAnim(cameraNode);
	//pManager->getSceneManager()->addCameraSceneNodeFPS(0, 80.0f, 1, -1, 0, 8, true, .4);
	healthbar = new PlayerHealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	PoManager = new PlaceObjects();
}

void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	healthbar->Draw(pManager->getDriver());
	PoManager->Update(cameraNode, pManager->GetCollManager(), pManager->GetMeta(), pManager->getDriver(), pManager->getSceneManager(), pManager->GetSelector(), pManager->GetAnim());
	//pManager->getDriver()->draw2DImage(m_titlePic, core::position2d<s32>(100, 50));
	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

void TestLevelState::KeyboardEvent(CGameManager* pManager) {

}

void TestLevelState::MouseEvent(CGameManager* pManager) {
	// Remember the mouse statess
	bool isDown = false;

	if (pManager->GetMouse() == EMIE_RMOUSE_PRESSED_DOWN)
	{
		isDown = true;
		// spawn turret function insert here
		PoManager->SpawnTurret(pManager->getDriver(), pManager->getSceneManager(), PoManager->intersection, pManager->GetSelector(), pManager->GetMeta());
		PoManager->CreateCollision(pManager->GetAnim(), pManager->getSceneManager(), cameraNode, pManager->GetMeta());
	}

	if (pManager->GetMouse() == EMIE_RMOUSE_LEFT_UP)
	{
		isDown = false;
	}
}