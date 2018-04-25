#pragma once
#include <irrlicht.h>

#include "IDFLAGS.h"
#include "MouseInput.h"
#include "EnemySpawner.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: video
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace video;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: scene
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace scene;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: std
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: core
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace core;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A place objects. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class PlaceObjects
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	/// <param name="smgr">  	[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PlaceObjects(IVideoDriver* driver, ISceneManager* smgr);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a ray. </summary>
	///
	/// <param name="camera">  	[in,out] If non-null, the camera. </param>
	/// <param name="selector">	[in,out] If non-null, the selector. </param>
	/// <param name="meta">	   	[in,out] If non-null, the meta. </param>
	/// <param name="anim">	   	[in,out] If non-null, the animation. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PlaceObjects(IVideoDriver* driver, ISceneManager* smgr, EnemySpawner* _spawner);
	void CreateRay(scene::ICameraSceneNode *camera, scene::ITriangleSelector * selector, scene::IMetaTriangleSelector *meta, scene::ISceneNodeAnimator* anim);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Spawn turret. </summary>
	///
	/// <param name="position">	The position. </param>
	/// <param name="selector">	[in,out] If non-null, the selector. </param>
	/// <param name="meta">	   	[in,out] If non-null, the meta. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a collision. </summary>
	///
	/// <param name="anim">  	[in,out] If non-null, the animation. </param>
	/// <param name="camera">	[in,out] If non-null, the camera. </param>
	/// <param name="meta">  	[in,out] If non-null, the meta. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void CreateCollision(ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates this object. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Update();

	/// <summary>	The intersection. </summary>
	vector3df intersection;
	/// <summary>	The hit triangle. </summary>
	triangle3df  hitTriangle;
	/// <summary>	The collided object. </summary>
	ISceneNode *collidedObject;
	/// <summary>	The ray. </summary>
	core::line3d<f32> ray;
	EnemySpawner* spawner;

private:
	/// <summary>	The driver. </summary>
	IVideoDriver * driver;
	/// <summary>	The smgr. </summary>
	ISceneManager * smgr;
	
	/// <summary>	The node. </summary>
	IMeshSceneNode* node;
};

