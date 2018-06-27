#include "TutorialState.h"
#include "GamePlayState.h"
#include "MenuState.h"
#include "TestLevelState.h"

TutorialState TutorialState::m_TutorialState;

TutorialState::TutorialState()
{
	// load level
	// spawn player
	// create observer
	// create enemy ( set position to -999999 or something )
	// spawn obstacleManager
	// spawn enemy
}

TutorialState* TutorialState::Instance() {
	return (&m_TutorialState);
}

void TutorialState::Init(CGameManager* pManager) {
	isReadyToShoot = true;
	isBuildPhase = true;
	// sound
	soundEngine = pManager->GetSoundEngine();
	soundEngine->setSoundVolume(.2f);
	soundEngine->play2D("media/Sound/Music/WesternOutside.wav", true);
	//timer
	timer = new Timer(pManager->getDevice());
	walkTimer = new Timer(pManager->getDevice());
	
	// Load level
	pManager->getDevice()->getCursorControl()->setVisible(false);
	pManager->getSceneManager()->loadScene("scene/TestScene.irr");
	pManager->SetCollision();

	//Create player
	player = new Player(pManager->getSceneManager(), pManager->getDriver(), pManager->GetAnim(), pManager->GetMeta());

	scene::IMesh* gun = pManager->getSceneManager()->getMesh("meshes/Nagant_Revolver.obj");
	gunNode = 0;
	gunNode = pManager->getSceneManager()->addMeshSceneNode(gun, player->getCamera(), 0);
	gunNode->setMaterialFlag(video::EMF_LIGHTING, false);
	gunNode->setMaterialTexture(0, pManager->getDriver()->getTexture("textures/Nagant_Revolver.png"));
	gunNode->setPosition(core::vector3df(1.5, -1.5, 2.5));
	gunNode->setScale(core::vector3df(0.3, 0.3, 0.3));

	std::vector<bool> obstacles;
	for (int i = 0; i < ((World_Size / Cell_Size) * (World_Size / Cell_Size)); i++)
		obstacles.push_back(false);

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
	grid = new Grid(obstacles);
	playerReticle = new Reticle(pManager->getDriver(), "media/UI/rsz_reticle.png");
	playerHealth = new PlayerHealth(pManager->getDriver(), "media/UI/UI_IsaacHeart.png");
	drawUI = new DrawUI(pManager->getDriver());


	// enemyManager
	playerCore = new PlayerBase(pManager->getSceneManager()->getSceneNodeFromName("house"), pManager->getSceneManager(), pManager->getDevice());
	cManager = new Currency();
	enemyManager = new EnemyManager(pManager->getSceneManager(), pManager->GetSelector(), pManager->GetMeta(), pManager->getDriver(), cManager, timer);
	waveManager = new WaveManager(pManager, playerCore, grid, enemyManager, timer);
	PoManager = new PlaceObjects(pManager->getDriver(), pManager->getSceneManager(), waveManager, cManager, enemyManager);
	PoManager->SpawnPlacementIndicator(vector3df(0, -1000, 0));

	opponent = new Opponent(pManager->getSceneManager()->getMesh("meshes/EnemyMesh.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, pManager->getSceneManager()->getSceneNodeFromName("Ground"), vector<GridCell*>(0), vector3df(0,0,0), core::vector3df(0, 0, 0), core::vector3df(1.0f, 1.0f, 1.0f), player, enemyManager);
	opponent->setPosition(vector3df(0, 0, 99999));
	scene::ITriangleSelector* selector = pManager->getSceneManager()->createTriangleSelector(opponent->getMesh(), opponent);
	opponent->setTriangleSelector(selector);
	pManager->GetMeta()->addTriangleSelector(selector);
	observer = new Observer();
	shootListener = new Listener();
	walkListener = new Listener();
	killEnemyListener = new Listener();
	spawnObstacleListener = new Listener();
	spawnTurretListener = new Listener();
	walkListener->Attach(observer);
	observer->SwitchState(WALK);
}

void TutorialState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();
	if (timer->alarm())  isReadyToShoot = true;
	if (isBuildPhase) {
		PoManager->Update(player->getCamera(), pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());
		drawUI->pSign->pSignImage = pManager->getDriver()->getTexture("media/UI/BuildPhaseSign.png");
	} else {
		PoManager->isInBuildMode = false;
		drawUI->pSign->ChangeImage(pManager->getDriver(), 0);
		drawUI->pBuildPhaseUI->isBuildPhase = false;
		PoManager->ResetPlacementIndicator();
		}

	drawUI->Draw(pManager->getDriver(), pManager->getGUIEnvironment());
	playerReticle->Draw(pManager->getDriver());
	playerHealth->Draw(pManager->getDriver(), player->health);

	if(walkTimer->alarm() && observer->now == WALK && walkingState) {
		walkListener->Notify(walkListener, SHOOT);
	shootListener->Attach(observer);
	}

	if (pManager->GetMouse() == EMIE_RMOUSE_PRESSED_DOWN && PoManager->objectToPlace == 1) {
		if (spawnObstacleListener->obs && observer->now == SPAWNOBSTACLE) {
			spawnObstacleListener->Notify(spawnObstacleListener, SPAWNTURRET);
			spawnTurretListener->Attach(observer);
		}
	}

	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

void TutorialState::Clear(CGameManager* pManager) {
	//delete player;
	//delete grid;
	//delete timer;
	//delete PoManager;
	//delete playerReticle;
	//delete playerHealth;
	//delete drawUI;
	//soundEngine = nullptr;
	delete gunNode;
	pManager->GetMeta()->removeTriangleSelector(player->getCamera()->getTriangleSelector());
	delete player;

	//pManager->getSceneManager()->clear();
}

void TutorialState::KeyboardEvent(CGameManager* pManager) {
	if (pManager->GetKeyboard() == KEY_ESCAPE) {
		pManager->ChangeState(TestLevelState::Instance());
	}
	// on kill enemy notify observer

	if(observer->now == WALK) {
		if (pManager->GetKeyboard() == KEY_KEY_W) {
			if (!walkingState) {
				walkTimer->stop();
				walkTimer->reset();
				walkTimer->start();
				walkTimer->set(400);
				walkingState = true;
			}
		}
	
	}

	// on place obstacle notify observer
	if (pManager->GetKeyboard() == KEY_KEY_E && isBuildPhase)
	{

		//trigger Placement indicator
		if (!PoManager->isInBuildMode)
		{
			PoManager->isInBuildMode = true;
			drawUI->pBuildPhaseUI->isBuildPhase = true;
		}
		else if (PoManager->isInBuildMode)
		{
			PoManager->isInBuildMode = false;
			drawUI->pBuildPhaseUI->isBuildPhase = false;
			PoManager->ResetPlacementIndicator();
		}
	}
	if (pManager->GetKeyboard() == KEY_KEY_1)
	{
		PoManager->objectToPlace = 1;
		PoManager->placementIndicatorNode->setMesh(pManager->getSceneManager()->getMesh("meshes/tempBarricade.obj"));
		PoManager->placementIndicatorNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		PoManager->placementIndicatorNode->setMaterialFlag(video::EMF_LIGHTING, false);
		PoManager->placementIndicatorNode->setMaterialTexture(0, pManager->getDriver()->getTexture("textures/editor_defaults/default_texture.png"));
		drawUI->pBuildPhaseUI->pBuildImage = drawUI->pBuildPhaseUI->pBarricadeImage;
	}
	if (pManager->GetKeyboard() == KEY_KEY_2)
	{
		PoManager->objectToPlace = 2;
		PoManager->placementIndicatorNode->setMesh(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"));
		PoManager->placementIndicatorNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		PoManager->placementIndicatorNode->setMaterialFlag(video::EMF_LIGHTING, false);
		PoManager->placementIndicatorNode->setMaterialTexture(0, pManager->getDriver()->getTexture("textures/editor_defaults/default_texture.png"));
		drawUI->pBuildPhaseUI->pBuildImage = drawUI->pBuildPhaseUI->pTurretImage;
	}
	// on place turret notify observer
}

void TutorialState::MouseEvent(CGameManager* pManager) {
	// on shoot notify observer
	if (pManager->GetMouse() == EMIE_RMOUSE_PRESSED_DOWN && isBuildPhase)
	{
		//	isDown = true;
		// spawn turret function insert here
		//	int idTest = PoManager->collidedObject->getID();
		//if (PoManager->collidedObject->getID() == IDFlag::spawnGround)
		//{
		const int turretCount = turretList.size();
		PoManager->CreateRay(player->getCamera(), pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim(), turretList);

		if(turretList.size() > turretCount) {
			if (spawnTurretListener->obs && observer->now == SPAWNTURRET) {
				spawnTurretListener->Notify(spawnTurretListener, ENDTUTORIAL);
				tutorialFinished = true;
				// set a timer, finish tut and change states
			}
		}
	}

	//! When the player is not in the building phase and pressed the left mouse button
	if (pManager->GetMouse() == EMIE_LMOUSE_PRESSED_DOWN) {
		if (isReadyToShoot) {
			soundEngine->play2D("media/Sound/gunshot.wav", false);
			//! returns the node the player will hit on shooting
			ISceneNode* node = player->RayCreate(pManager->GetSelector(), pManager->GetMeta(), player->getCamera(), pManager->getSceneManager());
			//! passes the node into the enemyManager which holds all the enemies
			if (node && node->getID() == 17) { // check if node is an enemy
				pManager->GetMeta()->removeTriangleSelector(node->getTriangleSelector());
				node->remove();
				if (observer->now == KILLENEMY) {
					if (killEnemyListener->obs) {
						killEnemyListener->Notify(killEnemyListener, SPAWNOBSTACLE);
						spawnObstacleListener->Attach(observer);
					}		
				}
			}
			if(shootListener->obs)
			if (shootListener->obs->now == SHOOT) {
				shootListener->Notify(shootListener, KILLENEMY);
				opponent->setPosition(vector3df(0, 0, 20));
				killEnemyListener->Attach(observer);
			}
			isReadyToShoot = false;
			//! timer that is called in the update loop which resets the isReadyToShoot boolean
			//! timer updates in miliseconds : 500 = 0.5 seconds
			timer->set(delayBetweenShots);
		}
	}
}

void TutorialState::TutorialCompleted() {
	// change gamestate to testlevelstate
}


TutorialState::~TutorialState()
{
}
