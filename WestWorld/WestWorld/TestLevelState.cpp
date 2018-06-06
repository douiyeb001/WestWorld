#include "TestLevelState.h"
#include "MenuState.h"
#include <memory>

TestLevelState TestLevelState::m_TestLevelState;
Timer* p_Timer;

TestLevelState::TestLevelState(){

}


TestLevelState::~TestLevelState(){

}

TestLevelState* TestLevelState::Instance(){
	return(&m_TestLevelState);
}

void TestLevelState::Init(CGameManager* pManager) {
	CGamePlayState::Init(pManager);
	waveCount = 1;
	readyToShoot = true;
	pauseManager = new PauseManager(pManager->getDriver(), pManager->getGUIEnvironment());
	p_Timer = new Timer(pManager->getDevice());
	pManager->getDevice()->getCursorControl()->setVisible(false);
	pManager->getSceneManager()->loadScene("scene/TestScene.irr");
	pManager->SetCollision();
	isBuildPhase = true;
	pPLayer = unique_ptr<Player>(new Player(pManager->getSceneManager(),pManager->getDriver(), pManager->GetAnim(), pManager->GetMeta()));

	//healthbar = new PlayerCore(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	//gun
	scene::IMesh* gun = pManager->getSceneManager()->getMesh("meshes/Nagant_Revolver.obj");
	gunNode = 0;
	gunNode = pManager->getSceneManager()->addMeshSceneNode(gun, pPLayer->getCamera(), 0);
	gunNode->setMaterialFlag(video::EMF_LIGHTING, false);
	gunNode->setMaterialTexture(0, pManager->getDriver()->getTexture("textures/Nagant_Revolver.png"));
	gunNode->setPosition(core::vector3df(1.5, -1.5, 2.5));
	gunNode->setScale(core::vector3df(0.3,0.3,0.3));


		for (int i = 0; i < ((World_Size / Cell_Size) * (World_Size / Cell_Size)); i++)
		obstacles.push_back(false);
	cManager = new Currency();
	//currencyUI = new CurrencyUI(pManager->getDriver(), "media/UI/rsz_1dollar.png", "media/UI/rsz_1rsz_infinity.png");
	pDrawUI = new DrawUI(pManager->getDriver());
	//currencyUI = new CurrencyUI(pManager->getDriver(), "media/UI/UI_Currency.png");

	pGameOver = new GameOverScreen(pManager->getDriver(), "media/UI/gameover.jpg");
	pVictory = new VictoryScreen(pManager->getDriver(), "media/UI/VictoryScreen.png");
	pWaveCounterUI = new WaveCounterUI(pManager->getDriver(),pManager->getGUIEnvironment());
	//pObjective = new Objective(pManager->getDriver(), "media/UI/ObjectiveNotDone.png", pManager->getDevice());


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
	playerCore = new PlayerBase(pManager->getSceneManager()->getSceneNodeFromName("house"), pManager->getSceneManager(),pManager->getDevice());
	//enemyManager = new EnemyManager(pManager->getSceneManager(),pManager->GetSelector(),pManager->GetMeta(),pManager->getDriver(), cManager);
	Timer* enemyTimer = new Timer(pManager->getDevice());
	(*enemyTimer).set(5000);
	//playerCore = new PlayerBase(pManager->getSceneManager()->getSceneNodeFromName("house"), pManager->getSceneManager());
	enemyManager = new EnemyManager(pManager->getSceneManager(),pManager->GetSelector(),pManager->GetMeta(),pManager->getDriver(), cManager,enemyTimer);
	pTurretAI = new TurretAI(enemyManager);
	spawnPoint = new EnemySpawner(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(),pManager->getSceneManager(),-2,vector3df(0,0,-350), vector3df(0,0,0),vector3df(1.0f,1.0f,1.0f), playerCore,obstacles, pManager->GetMeta() ,enemyManager, enemyTimer);
	//spawnPoint->drop();
	playerReticle = new Reticle(pManager->getDriver(), "media/UI/rsz_reticle.png");
	PoManager = new PlaceObjects(pManager->getDriver(), pManager->getSceneManager(), spawnPoint, cManager);
	pPlayerHealth = new PlayerHealth(pManager->getDriver(), "media/UI/UI_IsaacHeart.png");
//	//IMeshSceneNode* enemy = new Opponent(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, pManager->getSceneManager()->getSceneNodeFromName("Ground"),(*spawnPoint).path.finalpath, vector3df(0,0,0), vector3df(0, 0, 0), vector3df(0, 0, 0),);
//	//enemy->drop();
//	enemy = new Opponent(pManager->getSceneManager()->getSceneNodeFromId(1), pManager->getSceneManager()->getSceneNodeFromName("Ground"),playerCore, obstacles);
	
	PoManager->SpawnPlacementIndicator(vector3df(0, -1000, 0));
}

void TestLevelState::Clear(CGameManager* pManager) {
	pManager->getSceneManager()->clear();

	delete enemyManager;
	delete pTurretAI;
	delete spawnPoint;

	delete p_Timer;
	delete healthbar;
	delete currencyUI;
	delete playerReticle;
	delete playerCore;
	delete pauseManager;

	delete PoManager;
	delete cManager;
}

void TestLevelState::Update(CGameManager* pManager) {
	pauseManager->Draw();
	if (pauseManager->IsGamePaused()) {
		enemyManager->p_Timer->deltaTime();
		return;
	}

	if (p_Timer->alarm())  readyToShoot = true;
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	pTurretAI->GetList(enemyManager->GiveArray());
	pTurretAI->TurretShooting(pManager->getSceneManager(),pManager->getDevice());
	//enemy->Update();
	if (isBuildPhase) {

		PoManager->Update(pPLayer->getCamera(), pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());
		if (enemyManager->p_Timer->alarm()) {
			isBuildPhase = false;
			PoManager->isInBuildMode = false;
			pDrawUI->pSign->ChangeImage(pManager->getDriver(), waveCount);
			pDrawUI->pBuildPhaseUI->isBuildPhase = false;
			PoManager->ResetPlacementIndicator();
			spawnPoint->NewWave(10);
		}
	} else {
		/*float z = (*pPLayer).getCamera()->getPosition().Z;
		float x = (*pPLayer).getCamera()->getPosition().Y;	
		std::vector<GridCell*> list = (*spawnPoint).path->GetSurroundingCells((*pPLayer).getCamera()->getPosition());
		for (GridCell* g : list) {
			irr::core::aabbox3df box = irr::core::aabbox3df(g->x - Cell_Size / 2, x, g->y - Cell_Size / 2, g->x + Cell_Size / 2, x, g->y + Cell_Size / 2);
			pManager->getSceneManager()->addCubeSceneNode(5,NULL,10,vector3df(g->x, x, g->y));
		}*/
		enemyManager->Update((*spawnPoint).path->GetSurroundingCells((*pPLayer).getCamera()->getAbsolutePosition()));
		(*spawnPoint).Update();
		if (enemyManager->GiveArray().empty() && spawnPoint->enemiesInWave == 0) {
			enemyManager->p_Timer->set(5000);
			waveCount++;
			pDrawUI->pSign->pSignImage = pManager->getDriver()->getTexture("media/UI/BuildPhaseSign.png");
			isBuildPhase = true;
		}
	}
	
	pDrawUI->Draw(pManager->getDriver(), pManager->getGUIEnvironment());
	//currencyUI->Draw(pManager->getGUIEnvironment(), pManager->getDriver());
	PoManager->Update(pPLayer->getCamera(), pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());

	playerReticle->Draw(pManager->getDriver());
	pPlayerHealth->Draw(pManager->getDriver(), playerCore->health);

	pauseManager->Draw();
	if (playerCore->health <= 0) {
		pGameOver->Draw(pManager->getDriver());
	}
	//Set the amount of waves needed	
	if(waveCount == 3)
	{
		pVictory->Draw(pManager->getDriver());
	}

	//if (p_Timer->alarm()) readyToShoot = true;
	//pWaveCounterUI->Draw(pManager->getGUIEnvironment(),pManager->getDriver(),waveCount);
	pManager->getGUIEnvironment()->drawAll();

	pManager->getDriver()->endScene();
}

void TestLevelState::KeyboardEvent(CGameManager* pManager) {
	if(pManager->GetKeyboard() == KEY_ESCAPE)
		pauseManager->TogglePause();

	if (pauseManager->IsGamePaused()) {
		// every event that happens while in the pause state
		pauseManager->KeyboardEvent(pManager);
		//
		return;
	}

	if (pManager->GetKeyboard() == KEY_KEY_E && isBuildPhase)
	{
		
		//trigger Placement indicator
		if (!PoManager->isInBuildMode)
		{
			PoManager->isInBuildMode = true;
			pDrawUI->pBuildPhaseUI->isBuildPhase = true;
		}
		else if(PoManager->isInBuildMode)
		{
			PoManager->isInBuildMode = false;
			pDrawUI->pBuildPhaseUI->isBuildPhase = false;
			PoManager->ResetPlacementIndicator();
		}
	}
	if(pManager->GetKeyboard() == KEY_KEY_1)
	{
		PoManager->objectToPlace = 1;
		PoManager->placementIndicatorNode->setMesh(pManager->getSceneManager()->getMesh("meshes/tempBarricade.obj"));
		PoManager->placementIndicatorNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		PoManager->placementIndicatorNode->setMaterialFlag(video::EMF_LIGHTING, false);
		PoManager->placementIndicatorNode->setMaterialTexture(0, pManager->getDriver()->getTexture("textures/editor_defaults/default_texture.png"));
		pDrawUI->pBuildPhaseUI->pBuildImage = pDrawUI->pBuildPhaseUI->pBarricadeImage;
	}
	if (pManager->GetKeyboard() == KEY_KEY_2)
	{
		PoManager->objectToPlace = 2;
		PoManager->placementIndicatorNode->setMesh(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"));
		PoManager->placementIndicatorNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		PoManager->placementIndicatorNode->setMaterialFlag(video::EMF_LIGHTING, false);
		PoManager->placementIndicatorNode->setMaterialTexture(0, pManager->getDriver()->getTexture("textures/editor_defaults/default_texture.png"));
		pDrawUI->pBuildPhaseUI->pBuildImage = pDrawUI->pBuildPhaseUI->pTurretImage;
	}
}

void TestLevelState::MouseEvent(CGameManager* pManager) {
	if (pauseManager->IsGamePaused()) return;
	// Remember the mouse statess

	if (pManager->GetMouse() == EMIE_RMOUSE_PRESSED_DOWN && isBuildPhase)
	{
	//	isDown = true;
		// spawn turret function insert here
	//	int idTest = PoManager->collidedObject->getID();
		//if (PoManager->collidedObject->getID() == IDFlag::spawnGround)
		//{
		PoManager->CreateRay(pPLayer->getCamera(), pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());
	}
	
	if (pManager->GetMouse() == EMIE_LMOUSE_PRESSED_DOWN && !isBuildPhase) {
		if (readyToShoot) {
			ISceneNode* node = pPLayer->RayCreate(pManager->GetSelector(), pManager->GetMeta(), pPLayer->getCamera(), pManager->getSceneManager());
			enemyManager->CheckCollision(node);
			readyToShoot = false;
			p_Timer->set(500);
		}
	}
}