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
	pManager->getDevice()->getCursorControl()->setVisible(false);
	//m_titlePic = pManager->getDriver()->getTexture("media/fire.jpg");
	pManager->getSceneManager()->loadScene("scene/TurretSceneNew.irr");
	pPLayer = new Player(pManager->getSceneManager(),pManager->getDriver(), pManager->GetAnim());
	cameraNode = pPLayer->getCamera();
	pManager->SetAnim(cameraNode);
	cameraNode->addAnimator(pManager->GetAnim());
	p_Timer = new Timer(pManager->getDevice());
	pManager->SetCollision();
//	pManager->GetAnim()->drop();
	healthbar = new PlayerHealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	for (int i = 0; i < ((World_Size / Cell_Size) * (World_Size / Cell_Size)); i++)
		obstacles.push_back(false);
	cManager = new Currency();
	currencyUI = new CurrencyUI(pManager->getDriver(), "media/UI/rsz_1dollar.png", "media/UI/rsz_1rsz_infinity.png");
	
	
	//bool obstacles[1000];//[(World_Size / Cell_Size)*(World_Size / Cell_Size)];
	//std::fill(std::begin(obstacles), std::end(obstacles), false);

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
	enemyManager = new EnemyManager(pManager->getSceneManager(),pManager->GetSelector(),pManager->GetMeta(),pManager->getDriver(), cManager);
	pTurretAI = new TurretAI(enemyManager);
	spawnPoint = new EnemySpawner(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(),pManager->getSceneManager(),-2,vector3df(0,0,-350), vector3df(0,0,0),vector3df(1.0f,1.0f,1.0f), pManager->getSceneManager()->getSceneNodeFromName("house"),obstacles, pManager->GetMeta() ,enemyManager);
	spawnPoint->drop();
	playerReticle = new Reticle(pManager->getDriver(), "media/UI/rsz_reticle.png");

	PoManager = new PlaceObjects(pManager->getDriver(), pManager->getSceneManager(), spawnPoint, cManager);
	//IMeshSceneNode* enemy = new Opponent(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, pManager->getSceneManager()->getSceneNodeFromName("Ground"),(*spawnPoint).path.finalpath, vector3df(0,0,0), vector3df(0, 0, 0), vector3df(0, 0, 0),);
	//enemy->drop();
//	enemy = new Opponent(pManager->getSceneManager()->getSceneNodeFromId(1), pManager->getSceneManager()->getSceneNodeFromName("Ground"),playerCore, obstacles);
	(*spawnPoint).SpawnOpponent();
	PoManager->SpawnPlacementIndicator(vector3df(0, -1000, 0));
}

void TestLevelState::Clear(CGameManager* pManager) {

}
void TestLevelState::Update(CGameManager* pManager) {
	if (pause) return;

	if (p_Timer->alarm())  readyToShoot = true;
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	enemyManager->Update();
	pTurretAI->GetList(enemyManager->GiveArray());
	pTurretAI->TurretShooting(pManager->getSceneManager(),pManager->getDevice());
	//enemy->Update();
	(*spawnPoint).Update();
	healthbar->Draw(pManager->getDriver());
	currencyUI->Draw(pManager->getGUIEnvironment(), pManager->getDriver());
	PoManager->Update(cameraNode, pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());
	
	playerReticle->Draw(pManager->getDriver());
	//if (p_Timer->alarm()) readyToShoot = true;

	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

void TestLevelState::KeyboardEvent(CGameManager* pManager) {
	if (pManager->GetKeyboard() == KEY_ESCAPE) pause = !pause;

	if (pause) return;

	if(pManager->GetKeyboard() == KEY_KEY_E)
	{
		//trigger Placement indicator
		if (!PoManager->isInBuildMode)
		{
			PoManager->isInBuildMode = true;
		
		}
		else if(PoManager->isInBuildMode)
		{
			PoManager->isInBuildMode = false;
			PoManager->ResetPlacementIndicator();
			
		}
	}
}

void TestLevelState::MouseEvent(CGameManager* pManager) {
	if (pause) return;
	// Remember the mouse statess
	//bool isDown = false;
	int maxTime;

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
		if (readyToShoot) {
			ISceneNode* node = pPLayer->RayCreate(pManager->GetSelector(), pManager->GetMeta(), pPLayer->getCamera(), pManager->getSceneManager());
			enemyManager->CheckCollision(node);
			readyToShoot = false;
			p_Timer->set(500);
		}

	}
	if (pManager->GetMouse() == EMIE_RMOUSE_LEFT_UP)
	{
		//isDown = false;
	}

}