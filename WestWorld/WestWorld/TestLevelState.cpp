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
//	pManager->getSceneManager()->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));
	pManager->getSceneManager()->addCameraSceneNodeFPS(0, 80.0f, 1, -1, 0, 8, true, .4);
	healthbar = new HealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
}

void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	healthbar->Draw(pManager->getDriver());
	//pManager->getDriver()->draw2DImage(m_titlePic, core::position2d<s32>(100, 50));
	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

void TestLevelState::KeyboardEvent(CGameManager* pManager) {

}