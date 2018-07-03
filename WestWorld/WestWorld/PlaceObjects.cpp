#include "PlaceObjects.h"
#include "GridCell.h"
#include "TurretAI.h"

//#include "MouseInput.h"



PlaceObjects::PlaceObjects(ISoundEngine* iSoundEngine, IVideoDriver* iDriver, ISceneManager* iSmgr, WaveManager* _waveManager, Currency* _cManager, EnemyManager* enemyManager) : waveManager(_waveManager)
{
	driver = iDriver;
	smgr = iSmgr;
	cManager = _cManager;
	IEnemyManager = enemyManager;
	isInBuildMode = true;
	SoundEngine = iSoundEngine;
}

bool hasSpawnedTurret;

//This method will create a Turret after the ray has detected ground and update the meta with the Triangleselector of the placed turret
void PlaceObjects::SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta, ICameraSceneNode* camera, ISceneNodeAnimator* anim, vector<TurretAI*> &turretlist)
{

	//goal cell can't be chosen

	//path can't be blocked

	//player can't be on the cell

	//Tim & Daniel spawning objects
	//spawn a barricade
	if (objectToPlace == 1) {
		if (cManager->CheckCurrency(objectToPlace))
		{
			scene::IMesh* barrelMesh = smgr->getMesh("meshes/tempBarricade.obj");
			scene::IMeshSceneNode* barrelNode = 0;
			barrelNode = smgr->addMeshSceneNode(barrelMesh, 0, IDFlag::spawnedObstacle);
			if (barrelNode)
			{
				SoundEngine->play2D("media/Sound/CashSound.wav", false);
				barrelNode->setName("Barricade");
				barrelNode->setMaterialFlag(video::EMF_LIGHTING, false);
				barrelNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
				barrelNode->setScale(vector3df(1.2, 1.2, 1.2));
				barrelNode->setPosition((*waveManager).spawnPoints[0]->path->GetCentre(position));
				selector = smgr->createTriangleSelector(barrelNode->getMesh(), barrelNode);
				barrelNode->setTriangleSelector(selector);
				meta->addTriangleSelector(selector);
				selector->drop();
				for(int i = 0; i < (*waveManager).spawnPoints.size();i++)
					(*waveManager).spawnPoints[i]->_pEnemyManager->UpdatePath((*waveManager).spawnPoints[i]->path->currentPath, (*waveManager).spawnPoints[i]->path->GetCell(position));
				CreateCollision(anim, camera, meta);
				cManager->BuildingCost(barrelNode);

				SpawnExplosion(position, 10);
			}
			barrelNode = 0;
		}
	}

	//spawn a turret
	if (objectToPlace == 2) {
		if (cManager->CheckCurrency(objectToPlace))
		{
			scene::IMesh* turretTopMesh = smgr->getMesh("meshes/TurretTopMesh.obj");
			scene::IMeshSceneNode* turretNode = 0;			
			scene::IMesh* turretBottomMesh = smgr->getMesh("meshes/TurretBottomMesh.obj");
			scene::IMeshSceneNode* turretBottomNode = 0;
			turretNode = smgr->addMeshSceneNode(turretTopMesh, 0, IDFlag::spawnedTurret);
			turretBottomNode = smgr->addMeshSceneNode(turretBottomMesh, 0, IDFlag::spawnedTurret);
			if (turretNode)
			{
				SoundEngine->play2D("media/Sound/CashSound.wav", false);

				turretNode->setName("Turret");
				turretNode->setMaterialFlag(video::EMF_LIGHTING, false);
				turretNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
				turretNode->setPosition((*waveManager).spawnPoints[0]->path->GetCentre(position));
				turretBottomNode->setName("Turret");
				turretBottomNode->setMaterialFlag(video::EMF_LIGHTING, false);
				turretBottomNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
				turretBottomNode->setPosition((*waveManager).spawnPoints[0]->path->GetCentre(position));
				TurretAI* turret = new TurretAI(IEnemyManager, turretNode, smgr, SoundEngine);
				selector = smgr->createTriangleSelector(turretBottomNode->getMesh(), turretBottomNode);
				turretlist.push_back(turret);
				turretNode->setTriangleSelector(selector);
				meta->addTriangleSelector(selector);
				selector->drop();

			

				//meta->drop();
				for (int i = 0; i < (*waveManager).spawnPoints.size(); i++)
					(*waveManager).spawnPoints[i]->_pEnemyManager->UpdatePath((*waveManager).spawnPoints[i]->path->currentPath, (*waveManager).spawnPoints[i]->path->GetCell(position));
				CreateCollision(anim, camera, meta);
				cManager->BuildingCost(turretNode);
				turretList.push_back(turretNode);
			}

			turretNode = 0;
		}
	}




	
}

//this method will create collision between the player and the placed turret
void PlaceObjects::CreateCollision(scene::ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta)
{

	anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now
}

//This method will create a ray after the right mouse button is pressed and check if the ray hits the ground to spawn a new turret
 void PlaceObjects::CreateRay(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim, vector<TurretAI*> &turretlist) {
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 150.0f;
	//scene::ISceneNode * selectedSceneNode =
	smgr->getSceneCollisionManager()->getCollisionPoint(ray, meta, intersection, hitTriangle, collidedObject);
	if (collidedObject)
	if (collidedObject->getID() == IDFlag::spawnGround) {
		if(isPlacementValid(intersection, camera))
			SpawnTurret(intersection, selector, meta, camera, anim, turretlist);
		//SpawnTurret(vector3df(floor32(intersection.X / Cell_Size) * Cell_Size - Cell_Size/2, intersection.Y, floor32(intersection.Z / Cell_Size) * Cell_Size - Cell_Size / 2), selector, meta);
		
	}
	//collidedObject->drop();
}

 void PlaceObjects::SpawnPlacementIndicator(core::vector3df position) {
	 
	 if (objectToPlace == 1) {
		 placementIndicatorMesh = smgr->getMesh("meshes/tempBarricade.obj");
	 }
	 if (objectToPlace == 2) {
		 placementIndicatorMesh = smgr->getMesh("meshes/TurretMesh.obj");
	 }
	
	 placementIndicatorNode = 0;
	 placementIndicatorNode = smgr->addMeshSceneNode(placementIndicatorMesh, 0, 20);
	 placementIndicatorNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	 placementIndicatorNode->setMaterialFlag(video::EMF_LIGHTING, false);
	 placementIndicatorNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
	 placementIndicatorNode->setPosition(position);
 }

void PlaceObjects::ResetPlacementIndicator()
{
	placementIndicatorNode->setPosition(vector3df(0,-1000,0));
}

 void PlaceObjects::MovePlacementIndicator(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim)
{
	 if(isInBuildMode) {
		 ray.start = camera->getPosition();
		 ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 150.0f;
		 //scene::ISceneNode * selectedSceneNode =
		 smgr->getSceneCollisionManager()->getCollisionPoint(ray, meta, intersection, hitTriangle, collidedObject);
		 if (collidedObject) {
			 if (collidedObject->getID() == IDFlag::spawnGround)
			 {
				 placementIndicatorNode->setPosition((*waveManager).spawnPoints[0]->path->GetCentre(intersection));
			 }
		 }
	 }
}

void PlaceObjects::Update(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim){
	MovePlacementIndicator(camera, selector, meta, anim);
	if (objectToPlace == 2) {
		
	}
}
vector<TurretAI*> PlaceObjects::GiveList()
{
	return ITurretList;
}

bool PlaceObjects::isPlacementValid(vector3df intersection, ICameraSceneNode* player) {
	// object can't be place on goalnode cell
	GridCell* goalCell = (*waveManager).spawnPoints[0]->path->GetCell((*waveManager).spawnPoints[0]->goalNode->node->getPosition());
	const float radius = 20;
	GridCell* currentCell = (*waveManager).spawnPoints[0]->path->GetCell(player->getPosition());
	vector3df intersectingCell = (*waveManager).spawnPoints[0]->path->GetCentre(intersection);
	if ((*waveManager).spawnPoints[0]->path->GetCell(intersection) == goalCell) return false;
	else if (currentCell == (*waveManager).spawnPoints[0]->path->GetCell(intersection)) return false;
	else if ((intersectingCell.X >= player->getPosition().X - radius && intersectingCell.X <= player->getPosition().X + radius) &&
		(intersectingCell.Z >= player->getPosition().Z - radius && player->getPosition().Z - radius)) {
		return false;
	}
	for (int i = 0; i < (*waveManager).spawnPoints.size(); i++)
		if (!(*waveManager).spawnPoints[i]->path->RecalculatePath(intersection)) {
			return false;
		}
	return true;
}

vector<ISceneNode*> PlaceObjects::GiveTurretArray()
{
	return turretList;
}

void PlaceObjects::SpawnFireFX(core::vector3df position)
{
	scene::IParticleSystemSceneNode* ps =
		smgr->addParticleSystemSceneNode(false);

	scene::IParticleEmitter* em = ps->createBoxEmitter(
		core::aabbox3d<f32>(-7, 0, -7, 7, 1, 7), // emitter size
		core::vector3df(0.0f, 0.06f, 0.0f),   // initial direction
		80, 100,                             // emit rate
		video::SColor(0, 255, 255, 255),       // darkest color
		video::SColor(0, 255, 255, 255),       // brightest color
		800, 2000, 0,                         // min and max age, angle
		core::dimension2df(1.f, 1.f),         // min size
		core::dimension2df(50.f, 50.f));        // max size

	ps->setEmitter(em); // this grabs the emitter
	em->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

	ps->addAffector(paf); // same goes for the affector
	paf->drop();

	ps->setPosition(position);
	ps->setScale(core::vector3df(2, 2, 2));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

void PlaceObjects::SpawnPortalFX(core::vector3df position)
{
	scene::IParticleSystemSceneNode* ps =
		smgr->addParticleSystemSceneNode(false);

	scene::IParticleEmitter* portalEmitter = ps->createRingEmitter(
		core::vector3df(0.0f, 0.1f, 0.0f),   // ring centre
		10,			//radius
		1,          //ring thickness
		core::vector3df(0.0f, 0.0f, 0.0f),	//direction
		100, 100,			//min max particles per sec
		video::SColor(0, 255, 255, 255),       // darkest color
		video::SColor(0, 1, 1, 1),       // brightest color
		800, 2000, 0,                         // min and max age, angle
		core::dimension2df(1.f, 1.f),         // min size
		core::dimension2df(50.f, 50.f));        // max size

	ps->setEmitter(portalEmitter); // this grabs the emitter
	portalEmitter->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

	ps->addAffector(paf); // same goes for the affector
	paf->drop();

	ps->setPosition(position);
	ps->setRotation(core::vector3df(90,0,0));
	ps->setScale(core::vector3df(2, 2, 2));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("media/Particle_PortalTransp.png"));
	ps->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

void PlaceObjects::SpawnExplosion(core::vector3df position, int directionsAmount)
{
	for (int particleIterator = 1; particleIterator < directionsAmount+1; particleIterator++) {
		int flipper = -1;
		flipper*-1;
		scene::IParticleSystemSceneNode* ps =
			smgr->addParticleSystemSceneNode(false);

		scene::IParticleEmitter* em = ps->createBoxEmitter(
			core::aabbox3d<f32>(-7, 0, -7, 7, 1, 7),
			core::vector3df(0, 0, 0),   // initial direction
			2, 10,                             // emit rate
			video::SColor(0, 255, 255, 255),       // darkest color
			video::SColor(0, 255, 255, 255),       // brightest color
			120, 200, 0,                         // min and max age, angle
			core::dimension2df(1.f, 1.f),         // min size
			core::dimension2df(50.f, 50.f));        // max size

		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it

		IParticleAffector* paf = ps->createFadeOutParticleAffector(SColor(255,255,255,255));
	//	IParticleAffector* gravAf = ps->createGravityAffector(vector3df(0,0.05,0));
//		IParticleAffector* scaleAf = ps->createScaleParticleAffector(dimension2df(0,0));
		IParticleAffector* rotAf = ps->createRotationAffector(vector3df(particleIterator*10*flipper, particleIterator*10 * flipper, particleIterator*10 * flipper), position);
		
		ps->addAffector(paf); // same goes for the affector
	//	ps->addAffector(gravAf);
	//	ps->addAffector(scaleAf);
		ps->addAffector(rotAf);
		
		paf->drop();
	//	gravAf->drop();
	//	scaleAf->drop();
		rotAf->drop();

		ps->setPosition(core::vector3df(position.X, position.Y+20, position.Z));
		ps->setRotation(vector3df((rand() % 180), (rand() % 180), (rand() % 180)));
		//ps->setScale(core::vector3df(0.1, 0.2, 0.2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture("media/Particle_GreenSplat.png"));
		ps->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	}
}
