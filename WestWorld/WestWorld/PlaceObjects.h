#pragma once
#include <irrlicht.h>

//#include "IDFLAGS.h"
#include "MouseInput.h"

using namespace irr;
using namespace video;
using namespace scene;
using namespace std;
using namespace core;



class PlaceObjects
{
public:
	PlaceObjects(IVideoDriver* driver, ISceneManager* smgr);
	void SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta);
	void CreateCollision(ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta);
	void Update(ICameraSceneNode *camera, scene::ISceneCollisionManager *collMan, scene::IMetaTriangleSelector *meta, scene::ITriangleSelector *selector, scene::ISceneNodeAnimator *anim);

	vector3df intersection;
	triangle3df  hitTriangle;
	ISceneNode *collidedObject;

private:
	IVideoDriver * driver;
	ISceneManager * smgr;
	core::line3d<f32> ray;
	IMeshSceneNode* node;
};

