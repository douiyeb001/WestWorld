#include <irrlicht.h>
#include "driverChoice.h"
#include "Opponent.h"
#include "PlayerBase.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

void AddScripts(scene::ISceneNode* node_, Opponent* enemy)
{
	if (!node_)
		return;

	// Do something with the node here.

	// recursive call to children
	core::list<scene::ISceneNode*> children = node_->getChildren();
	core::list<scene::ISceneNode*>::Iterator it = children.begin();
	for (; it != children.end(); ++it)
	{
		s32 id = (*it)->getID();
		if (id == 1)
		*enemy = Opponent(*it);
		AddScripts(*it, enemy);
	}
}

int main(int argc, char** argv)
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// create device and exit if creation failed

	IrrlichtDevice* device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Load .irr file example");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	// load the scene
	if (argc>1)
		smgr->loadScene(argv[1]);
	else
		smgr->loadScene("scene/terrain.irr");
	scene::ICameraSceneNode * camera = smgr->addCameraSceneNodeFPS(0, 50.f, 0.1f);

	// Create a meta triangle selector to hold several triangle selectors.
	scene::IMetaTriangleSelector * meta = smgr->createMetaTriangleSelector();
	core::array<scene::ISceneNode *> nodes;
	smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

	for (u32 i = 0; i < nodes.size(); ++i)
	{
		scene::ISceneNode * node = nodes[i];
		scene::ITriangleSelector * selector = 0;

		switch (node->getType())
		{
		case scene::ESNT_CUBE:
		case scene::ESNT_ANIMATED_MESH:
			// Because the selector won't animate with the mesh,
			// and is only being used for camera collision, we'll just use an approximate
			// bounding box instead of ((scene::IAnimatedMeshSceneNode*)node)->getMesh(0)
			selector = smgr->createTriangleSelectorFromBoundingBox(node);
			break;

		case scene::ESNT_MESH:
		case scene::ESNT_SPHERE: // Derived from IMeshSceneNode
			selector = smgr->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;
			
		case scene::ESNT_TERRAIN:
			selector = smgr->createTerrainTriangleSelector((scene::ITerrainSceneNode*)node);
			break;

		case scene::ESNT_OCTREE:
			selector = smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;

		default:
			// Don't create a selector for this node type
			break;
		}

		if (selector)
		{
			// Add it to the meta selector, which will take a reference to it
			meta->addTriangleSelector(selector);
			// And drop my reference to it, so that the meta selector owns it.
			selector->drop();
		}
	}
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));
	meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now

				  // And set the camera position so that it doesn't start off stuck in the geometry
	camera->setPosition(core::vector3df(0.f, 20.f, 0.f));


	// Point the camera at the cube node, by finding the first node of type ESNT_CUBE
	//scene::ISceneNode * target = smgr->getSceneNodeFromName("house");

	PlayerBase* newTarget = new PlayerBase(smgr->getSceneNodeFromName("house"),smgr);
	PlayerBase target = *newTarget;

	//scene::ISceneNode * enemy = smgr->getSceneNodeFromId(1);

	//Opponent* newEnemy = new Opponent(smgr->getSceneNodeFromId(1));
	Opponent* newEnemy = new Opponent(smgr->getRootSceneNode());
	Opponent enemy = *newEnemy;
	//enemy.enemy = smgr->getSceneNodeFromId(1);
	//Opponent enemy = Opponent();
	AddScripts(smgr->getRootSceneNode(),&enemy);

	scene::ISceneNode * ground = smgr->getSceneNodeFromName("Plane");

	if (enemy.enemy)
		camera->setTarget(enemy.enemy->getAbsolutePosition());


	target.healthBar->setMaterialTexture(0, driver->getTexture("media/HealthBarTexture.png")); // set diffuse texture

	int lastFPS = -1;

	while (device->run())
		if (device->isWindowActive())
		{
			if (enemy.active) {
				enemy.enemy->setPosition(enemy.enemy->getPosition() + (target.base->getPosition() - enemy.enemy->getPosition()) / 1000);

				enemy.collidesWithTarget(target);

				while (enemy.collidesWith(ground))
					enemy.enemy->setPosition(enemy.enemy->getPosition() + core::vector3df(0, 0.001f, 0));

				//enemy.Despawn();
			}

			float angle = atan2(camera->getAbsolutePosition().Z - target.healthBar->getAbsolutePosition().Z, camera->getAbsolutePosition().X - target.healthBar->getAbsolutePosition().X) *57.2957795131;
			target.healthBar->setRotation(irr::core::vector3df(0,45 -angle, 0));

			driver->beginScene(true, true, video::SColor(0, 200, 200, 200));
			smgr->drawAll();
			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				core::stringw str = L"Load Irrlicht File example - Irrlicht Engine [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}

		}

	device->drop();

	return 0;
}
