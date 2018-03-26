#include "PlaceObjects.h"
//#include "MouseInput.h"



PlaceObjects::PlaceObjects()
{

}
core::line3d<f32> ray;

bool hasSpawnedTurret;

//spawning the turret with thw correct data. Tim & Daniel
void PlaceObjects::SpawnTurret(video::IVideoDriver *driver, scene::ISceneManager *smgr, core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta, IDFlag flag)
{

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

//Give the camera collision with the new spawned turret. Tim And Daniel
void PlaceObjects::CreateCollision(scene::ISceneNodeAnimator *anim, scene::ISceneManager *smgr, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta)
{

	anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator
}

//Non stop check if a turret needs to be spawned Tim And Daniel
void PlaceObjects::Update(MouseInput input, ICameraSceneNode *camera, scene::ISceneCollisionManager *collMan, scene::IMetaTriangleSelector *meta, video::IVideoDriver *driver, scene::ISceneManager *smgr, scene::ITriangleSelector *selector, scene::ISceneNodeAnimator *anim, IrrlichtDevice *device)
{
	// All intersections in this example are done with a ray cast out from the camera to
	// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
	// trajectory or a sword's position, or create a ray from a mouse click position using
	// ISceneCollisionManager::getRayFromScreenCoordinates()
	
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 100.0f;

	// Tracks the current intersection point with the level or a mesh
	core::vector3df intersection;
	// Used to show with triangle has been hit
	core::triangle3df hitTriangle;

	scene::ISceneNode * collidedObject;

	if (collMan->getCollisionPoint(
		ray, meta, intersection, hitTriangle, collidedObject)) {
		if (collidedObject->getID() == IDFlag::spawnGround)
		{
			if (input.GetMouseState().isRightButtonDown)
			{
				if (!hasSpawnedTurret)
				{
					SpawnTurret(driver, smgr, intersection, selector, meta, IDFlag::spawnedObject);
					CreateCollision(anim, smgr, camera, meta);
					hasSpawnedTurret = true;
				}
			}
			else if (!input.GetMouseState().isRightButtonDown)
			{
				hasSpawnedTurret = false;
			}
		}

	}
}
