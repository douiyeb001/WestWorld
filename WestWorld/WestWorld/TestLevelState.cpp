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
	pManager->getSceneManager()->loadScene("scene/T_Placing.irr");
	pPLayer = new Player(pManager->getSceneManager(),pManager->getDriver(), pManager->GetAnim());
	cameraNode = pPLayer->getCamera();

	pManager->SetAnim(cameraNode);
	cameraNode->addAnimator(pManager->GetAnim());

	pManager->SetCollision();
	pManager->GetAnim()->drop();
	healthbar = new PlayerHealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	PoManager = new PlaceObjects(pManager->getDriver(), pManager->getSceneManager());
	
	
}

void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();


	PoManager->Update();
	
	healthbar->Draw(pManager->getDriver());

	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

void TestLevelState::KeyboardEvent(CGameManager* pManager) {

}

void TestLevelState::MouseEvent(CGameManager* pManager) {
	// Remember the mouse statess
	//bool isDown = false;

	if (pManager->GetMouse() == EMIE_RMOUSE_PRESSED_DOWN)
	{
	//	isDown = true;
		// spawn turret function insert here
	//	int idTest = PoManager->collidedObject->getID();
		//if (PoManager->collidedObject->getID() == IDFlag::spawnGround)
		//{
		PoManager->CreateRay(cameraNode, pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());		
	}

	if (pManager->GetMouse() == EMIE_LMOUSE_PRESSED_DOWN) {
		pPLayer->RayCreate(pManager->GetSelector(), pManager->GetMeta(),cameraNode, pManager->getSceneManager());
		
	}
	if (pManager->GetMouse() == EMIE_RMOUSE_LEFT_UP)
	{
		//isDown = false;
	}
}