#include <irrlicht.h>
#include "driverChoice.h"


using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int main(int argc, char** argv)
{

	core::vector3df moveForward = core::vector3df(0, 0, 1);

	// ask user for driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// create device and exit if creation failed

		IrrlichtDevice * device = createDevice(driverType,
			core::dimension2d<u32>(640, 480), 16, false, false, false);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Load .irr file example");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	// load the scene
	if (argc>1)
		smgr->loadScene(argv[1]);
	else
		smgr->loadScene("scene/testSceneCube.irr");

	//wasd navigation
	SKeyMap keyMap[9];

	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;

	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;

	ICameraSceneNode * camera = camera = smgr->addCameraSceneNodeFPS(0, 80.0f, 0.5, -1, keyMap, 8, true, 5);


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

	
	scene::ISceneNode * player = smgr->getSceneNodeFromName("Dwarf");


	player->setParent(camera);

	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, 0, 0));
	meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now

				  // And set the camera position so that it doesn't start off stuck in the geometry
	camera->setPosition(core::vector3df(0.f, 20.f, 0.f));

	// Point the camera at the cube node, by finding the first node of type ESNT_CUBE

	int lastFPS = -1;
	

	u32 then = device->getTimer()->getTime();
	// This is the movemen speed in units per second.
	const f32 MOVEMENT_SPEED = 10.f;
	while (device->run())
		if (device->isWindowActive())
		{
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 10.f; // Time in seconds
			then = now;
			
			driver->beginScene(true, true, video::SColor(255, 113, 113, 133));

			driver->beginScene(true, true, video::SColor(0, 200, 200, 200));
			smgr->drawAll();
			driver->endScene();
			if (KEY_KEY_J) 
			{
				camera->setPosition((camera->getPosition()) + vector3df(0.0f, 7.0f, 0.0f));
			}

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
