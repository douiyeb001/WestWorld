#include "PlaceObjects.h"
//#include "MouseInput.h"



PlaceObjects::PlaceObjects(IVideoDriver* iDriver, ISceneManager* iSmgr)
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
	scene::ISceneNode * selectedSceneNode =
		smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle,
			0);
	if (selectedSceneNode->getID() == 14) {
		SpawnTurret(intersection, selector, meta);
		//CreateCollision(anim, camera, meta);
	}



	 selectedSceneNode = 0;
}

void PlaceObjects::Update(){

}
