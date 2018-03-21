#pragma once
#include <irrlicht.h>

#include "IDFLAGS.h"

using namespace irr;

class PlaceObjects
{
public:
	PlaceObjects();
	void SpawnTurret(video::IVideoDriver *driver, scene::ISceneManager *smgr, core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta, IDFlag flag);
	void CreateCollision(scene::ISceneNodeAnimator *anim, scene::ISceneManager *smgr, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta);
};

