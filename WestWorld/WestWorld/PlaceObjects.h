#pragma once
#include <irrlicht.h>

#include "IDFLAGS.h"
#include "MouseInput.h"

using namespace irr;
using namespace video;
using namespace scene;
using namespace std;
using namespace core;



class PlaceObjects
{
public:
	PlaceObjects();
	void SpawnTurret(video::IVideoDriver *driver, scene::ISceneManager *smgr, core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta);
	void CreateCollision(ISceneNodeAnimator *anim, scene::ISceneManager *smgr, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta);
	void Update(ICameraSceneNode *camera, scene::ISceneCollisionManager *collMan, scene::IMetaTriangleSelector *meta, video::IVideoDriver *driver, scene::ISceneManager *smgr, scene::ITriangleSelector *selector, scene::ISceneNodeAnimator *anim);

	vector3df intersection;
	triangle3df  hitTriangle;
	ISceneNode * collidedObject;

private:
	//line3d<f32>* ray;
};

