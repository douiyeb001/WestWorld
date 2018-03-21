#include "PlaceObjects.h"



PlaceObjects::PlaceObjects()
{

}

void PlaceObjects::SpawnTurret(video::IVideoDriver *driver, scene::ISceneManager *smgr, core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta, IDFlag flag)
{

	//Tim & Daniel spawning objects
	scene::IMesh* barrelMesh = smgr->getMesh("meshes/Barrel.obj");
	scene::IMeshSceneNode* barrelNode = smgr->addMeshSceneNode(barrelMesh, 0, flag);

	if (barrelNode)
	{

		barrelNode->setMaterialFlag(video::EMF_LIGHTING, false);
		barrelNode->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
		barrelNode->setPosition(position);
		selector = smgr->createTriangleSelector(((scene::IMeshSceneNode*)barrelNode)->getMesh(), barrelNode);


	}
	if (selector)
	{
		// Add it to the meta selector, which will take a reference to it
		meta->addTriangleSelector(selector);
		// And drop my reference to it, so that the meta selector owns it.
		selector->drop();
	}

}

void PlaceObjects::CreateCollision(scene::ISceneNodeAnimator *anim, scene::ISceneManager *smgr, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta)
{

	anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));
	//meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now
}
