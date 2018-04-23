#include "PlaceObjects.h"
//#include "MouseInput.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="iDriver">	[in,out] If non-null, zero-based index of the driver. </param>
/// <param name="iSmgr">  	[in,out] If non-null, zero-based index of the smgr. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

PlaceObjects::PlaceObjects(IVideoDriver* iDriver, ISceneManager* iSmgr)
{
	driver = iDriver;
	smgr = iSmgr;

}

/// <summary>	True if has spawned turret, false if not. </summary>
bool hasSpawnedTurret;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Spawn turret. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="position">	The position. </param>
/// <param name="selector">	[in,out] If non-null, the selector. </param>
/// <param name="meta">	   	[in,out] If non-null, the meta. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PlaceObjects::SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta)
{

	//Tim & Daniel spawning objects
	/// <summary>	The barrel mesh. </summary>
	scene::IMesh* barrelMesh = smgr->getMesh("meshes/Barrel.obj");
	/// <summary>	The barrel node. </summary>
	scene::IMeshSceneNode* barrelNode = 0;
	/// <summary>	. </summary>
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates a collision. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="anim">  	[in,out] If non-null, the animation. </param>
/// <param name="camera">	[in,out] If non-null, the camera. </param>
/// <param name="meta">  	[in,out] If non-null, the meta. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PlaceObjects::CreateCollision(scene::ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta)
{

	anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));
	//meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// <summary>	Creates a ray. </summary>
 ///
 /// <remarks>	Rache, 23-Apr-18. </remarks>
 ///
 /// <param name="camera">  	[in,out] If non-null, the camera. </param>
 /// <param name="selector">	[in,out] If non-null, the selector. </param>
 /// <param name="meta">		[in,out] If non-null, the meta. </param>
 /// <param name="anim">		[in,out] If non-null, the animation. </param>
 ////////////////////////////////////////////////////////////////////////////////////////////////////

 void PlaceObjects::CreateRay(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim) {
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 100.0f;
	//scene::ISceneNode * selectedSceneNode =
	smgr->getSceneCollisionManager()->getCollisionPoint(ray, meta, intersection, hitTriangle, collidedObject);
			
	if (collidedObject->getID() == IDFlag::spawnGround) {
		SpawnTurret(intersection, selector, meta);
		CreateCollision(anim, camera, meta);
	}



	 //collidedObject = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates this object. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PlaceObjects::Update(){

}
