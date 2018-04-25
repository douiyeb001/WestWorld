#pragma once
#include <irrlicht.h>

#include "IDFLAGS.h"
#include "MouseInput.h"
#include "EnemySpawner.h"

using namespace irr;
using namespace video;
using namespace scene;
using namespace std;
using namespace core;



class PlaceObjects
{
public:
	PlaceObjects(IVideoDriver* driver, ISceneManager* smgr, EnemySpawner* _spawner);
	void CreateRay(scene::ICameraSceneNode *camera, scene::ITriangleSelector * selector, scene::IMetaTriangleSelector *meta, scene::ISceneNodeAnimator* anim);
	void SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta);
	void CreateCollision(ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta);
	
	void Update();

	vector3df intersection;
	triangle3df  hitTriangle;
	ISceneNode *collidedObject;
	core::line3d<f32> ray;
	EnemySpawner* spawner;

private:
	IVideoDriver * driver;
	ISceneManager * smgr;
	
	IMeshSceneNode* node;
};

