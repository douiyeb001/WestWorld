#include "PlaceObjects.h"
#include "GridCell.h"
//#include "MouseInput.h"



PlaceObjects::PlaceObjects(IVideoDriver* iDriver, ISceneManager* iSmgr, EnemySpawner* _spawner): spawner(_spawner)
{
	driver = iDriver;
	smgr = iSmgr;

}

bool hasSpawnedTurret;

void PlaceObjects::SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta)
{

	//Tim & Daniel spawning objects
	scene::IMesh* barrelMesh = smgr->getMesh("meshes/Barrel.obj");
	scene::IMeshSceneNode* barrelNode = 0;
	barrelNode = smgr->addMeshSceneNode(barrelMesh, 0, 15);

	if (barrelNode)
	{
		barrelNode->setMaterialFlag(video::EMF_LIGHTING, false);
		barrelNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
		barrelNode->setPosition(position);
		selector = smgr->createTriangleSelector(barrelNode->getMesh(), barrelNode);
		barrelNode->setTriangleSelector(selector);
		meta->addTriangleSelector(selector);
		selector->drop();
		meta->drop();
		spawner->path->RecalculatePath(position);
	}
	barrelNode = 0;
}

void PlaceObjects::CreateCollision(scene::ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta)
{

	anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));
	//meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now
}

 void PlaceObjects::CreateRay(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim) {
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 100.0f;
	//scene::ISceneNode * selectedSceneNode =
	smgr->getSceneCollisionManager()->getCollisionPoint(ray, meta, intersection, hitTriangle, collidedObject);
	if (collidedObject)
	if (collidedObject->getID() == IDFlag::spawnGround) {
		SpawnTurret(spawner->path->getCentre(intersection), selector, meta);
		//SpawnTurret(vector3df(floor32(intersection.X / Cell_Size) * Cell_Size - Cell_Size/2, intersection.Y, floor32(intersection.Z / Cell_Size) * Cell_Size - Cell_Size / 2), selector, meta);
		CreateCollision(anim, camera, meta);
	}



	 //collidedObject = 0;
}

void PlaceObjects::Update(){

}
