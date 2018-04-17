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
	pPLayer = new Player(pManager->getSceneManager(),pManager->getDriver(), pManager->GetAnim());
	cameraNode = pPLayer->getCamera();

	pManager->SetAnim(cameraNode);
	cameraNode->addAnimator(pManager->GetAnim());

	pManager->SetCollision();
	pManager->GetAnim()->drop();
	healthbar = new PlayerHealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	PoManager = new PlaceObjects(pManager->getDriver(), pManager->getSceneManager());
	
	//bool obstacles[1000];//[(World_Size / Cell_Size)*(World_Size / Cell_Size)];
	std::fill(std::begin(obstacles), std::end(obstacles), false);

	irr::core::list<scene::ISceneNode*> children = pManager->getSceneManager()->getRootSceneNode()->getChildren();
	core::list<scene::ISceneNode*>::Iterator it = children.begin();
	for (; it != children.end(); ++it)
	{
		if ((*it)->getID()) {
			s32 id = (*it)->getID();
			if (id == 10)

				for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++) {
					for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++) {
						// Do something with the node here.
						irr::core::aabbox3df box = irr::core::aabbox3df(x *Cell_Size - Cell_Size / 2, 0, z *Cell_Size - Cell_Size / 2, (x + 1)*Cell_Size + Cell_Size / 2, 0, (z + 1)*Cell_Size + Cell_Size / 2);

						if ((*it)->getTransformedBoundingBox().intersectsWithBox(box))
						{
							obstacles[((x)+World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z)+World_Size / (2 * Cell_Size))] = true;
						}
					}
				}
		}
	}
	playerCore = new PlayerBase(pManager->getSceneManager()->getSceneNodeFromName("house"), pManager->getSceneManager());
	enemy = new Opponent(pManager->getSceneManager()->getSceneNodeFromId(1), pManager->getSceneManager()->getSceneNodeFromName("Ground"),playerCore, obstacles);
}

void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();

	enemy->Update();
	
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