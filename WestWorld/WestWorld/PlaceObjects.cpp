#include "PlaceObjects.h"
#include "GridCell.h"
//#include "MouseInput.h"



PlaceObjects::PlaceObjects(IVideoDriver* iDriver, ISceneManager* iSmgr, EnemySpawner* _spawner, Currency* _cManager) : spawner(_spawner)
{
	driver = iDriver;
	smgr = iSmgr;
	cManager = _cManager;
}

bool hasSpawnedTurret;

//This method will create a Turret after the ray has detected ground and update the meta with the Triangleselector of the placed turret
void PlaceObjects::SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta, ICameraSceneNode* camera, ISceneNodeAnimator* anim)
{


	//Tim & Daniel spawning objects
	//spawn a barricade
	if (objectToPlace == 1) {
		if (cManager->CheckCurrency())
		{
			scene::IMesh* barrelMesh = smgr->getMesh("meshes/tempBarricade.obj");
			scene::IMeshSceneNode* barrelNode = 0;
			barrelNode = smgr->addMeshSceneNode(barrelMesh, 0, IDFlag::spawnedObstacle);
			if (barrelNode)
			{
				barrelNode->setName("Barricade");
				barrelNode->setMaterialFlag(video::EMF_LIGHTING, false);
				barrelNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
				barrelNode->setScale(vector3df(1.2, 1.2, 1.2));
				barrelNode->setPosition(spawner->path->GetCentre(position));
				selector = smgr->createTriangleSelector(barrelNode->getMesh(), barrelNode);
				barrelNode->setTriangleSelector(selector);
				meta->addTriangleSelector(selector);
				selector->drop();
				//meta->drop();
				if (spawner->path->RecalculatePath(position))
					spawner->_pEnemyManager->UpdatePath(spawner->path->currentPath, spawner->path->GetCell(position));
				CreateCollision(anim, camera, meta);
				cManager->BuildingCost(barrelNode);
			}
			barrelNode = 0;
		}
	}

	//spawn a turret
	if (objectToPlace == 2) {
		if (cManager->CheckCurrency())
		{
			scene::IMesh* turretMesh = smgr->getMesh("meshes/Barrel.obj");
			scene::IMeshSceneNode* turretNode = 0;
			turretNode = smgr->addMeshSceneNode(turretMesh, 0, IDFlag::spawnedTurret);
			if (turretNode)
			{
				turretNode->setName("Turret");
				turretNode->setMaterialFlag(video::EMF_LIGHTING, false);
				turretNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
				turretNode->setPosition(spawner->path->GetCentre(position));
				selector = smgr->createTriangleSelector(turretNode->getMesh(), turretNode);
				turretNode->setTriangleSelector(selector);
				meta->addTriangleSelector(selector);
				selector->drop();
				//meta->drop();
				if (spawner->path->RecalculatePath(position))
					spawner->_pEnemyManager->UpdatePath(spawner->path->currentPath, spawner->path->GetCell(position));
				CreateCollision(anim, camera, meta);
				cManager->BuildingCost(turretNode);
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
 void PlaceObjects::CreateRay(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim) {
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 150.0f;
	//scene::ISceneNode * selectedSceneNode =
	smgr->getSceneCollisionManager()->getCollisionPoint(ray, meta, intersection, hitTriangle, collidedObject);
	if (collidedObject)
	if (collidedObject->getID() == IDFlag::spawnGround) {
		SpawnTurret(intersection, selector, meta, camera, anim);
		//SpawnTurret(vector3df(floor32(intersection.X / Cell_Size) * Cell_Size - Cell_Size/2, intersection.Y, floor32(intersection.Z / Cell_Size) * Cell_Size - Cell_Size / 2), selector, meta);
		
	}
	//collidedObject->drop();
}

 void PlaceObjects::SpawnPlacementIndicator(core::vector3df position) {
	 
	 if (objectToPlace == 1) {
		 placementIndicatorMesh = smgr->getMesh("meshes/tempBarricade.obj");
	 }
	 if (objectToPlace == 2) {
		 placementIndicatorMesh = smgr->getMesh("meshes/Barrel.obj");
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
				 placementIndicatorNode->setPosition(spawner->path->GetCentre(intersection));
			 }
		 }
	 }
}

void PlaceObjects::Update(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim){
	MovePlacementIndicator(camera, selector, meta, anim);
	if (objectToPlace == 2) {
		
	}
}
