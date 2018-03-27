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
	pPLayer = new Player(pManager->getSceneManager());
	//pPLayer->CreatePlayer(pManager->getSceneManager());
	cameraNode = pPLayer->getCamera();

	pManager->SetAnim(cameraNode);
	cameraNode->addAnimator(pManager->GetAnim());
	pManager->GetAnim()->drop();
	healthbar = new PlayerHealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	PoManager = new PlaceObjects();
	
}

void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	healthbar->Draw(pManager->getDriver());
	PoManager->Update(cameraNode, pManager->GetCollManager(), pManager->GetMeta(), pManager->GetSelector(), pManager->GetAnim());
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
		PoManager->SpawnTurret(PoManager->intersection, pManager->GetSelector(), pManager->GetMeta());
		PoManager->CreateCollision(pManager->GetAnim(), cameraNode, pManager->GetMeta());
	}

	if (pManager->GetMouse() == EMIE_RMOUSE_LEFT_UP)
	{
		isDown = false;
	}
}