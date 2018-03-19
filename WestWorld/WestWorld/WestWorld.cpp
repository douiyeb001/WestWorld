#include <irrlicht.h>
#include "driverChoice.h"
#include "CAppReceiver.h"


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

enum
{

	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};
	int main(int argc, char** argv)
	{
		CAppReceiver appReceiver;		

		core::vector3df moveForward = core::vector3df(0, 0, 1);

		// ask user for driver
		video::E_DRIVER_TYPE driverType = driverChoiceConsole();
		if (driverType == video::EDT_COUNT)
			return 1;

		// create device and exit if creation failed

		IrrlichtDevice * device = createDevice(driverType,
			core::dimension2d<u32>(640, 480), 16, false, false, false,&appReceiver);

		if (device == 0)
			return 1; // could not create selected driver.

		device->setWindowCaption(L"Load .irr file example");

		video::IVideoDriver* driver = device->getVideoDriver();
		scene::ISceneManager* smgr = device->getSceneManager();

		// load the scene
		if (argc > 1)
			smgr->loadScene(argv[1]);
		else
			smgr->loadScene("scene/testSceneCube.irr");

		//wasd navigation
		SKeyMap keyMap[9];

		keyMap[0].Action = EKA_MOVE_FORWARD;
		keyMap[0].KeyCode = KEY_KEY_W;

		keyMap[1].Action = EKA_MOVE_BACKWARD;
		keyMap[1].KeyCode = KEY_KEY_S;

		keyMap[2].Action = EKA_STRAFE_LEFT;
		keyMap[2].KeyCode = KEY_KEY_A;

		keyMap[3].Action = EKA_STRAFE_RIGHT;
		keyMap[3].KeyCode = KEY_KEY_D;

		keyMap[4].Action = EKA_JUMP_UP;
		keyMap[4].KeyCode = KEY_SPACE;
		f32 MOVEMENT_SPEED = 0.3f;

		//Add Camera 
		ICameraSceneNode *  camera = smgr->addCameraSceneNodeFPS(0, 80.0f, MOVEMENT_SPEED, ID_IsNotPickable, keyMap, 8, true, .3f);

		scene::ITriangleSelector* selector = 0;

		

		if (selector)
		{
			scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
				selector, camera, core::vector3df(30, 50, 30),
				core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
			selector->drop(); // As soon as we're done with the selector, drop it.
			camera->addAnimator(anim);
			anim->drop();  // And likewise, drop the animator when we're done referring to it.
		}
	
		// Create a meta triangle selector to hold several triangle selectors.
		scene::IMetaTriangleSelector * meta = smgr->createMetaTriangleSelector();
		core::array<scene::ISceneNode *> nodes;
		smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

		//Collision Script 
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
		
		

		scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			meta, camera, core::vector3df(5, 5, 5),
			core::vector3df(0, -.981f, 0));
		meta->drop(); // I'm done with the meta selector now

		camera->addAnimator(anim);
		anim->drop(); // I'm done with the animator now

					  // And set the camera position so that it doesn't start off stuck in the geometry
		camera->setPosition(core::vector3df(0.f, 20.f, 0.f));


		int lastFPS = -1;

		u32 then = device->getTimer()->getTime();
		while (device->run())
			if (device->isWindowActive())
			{
				const u32 now = device->getTimer()->getTime();
				const f32 frameDeltaTime = (f32)(now - then) / 10.f; // Time in seconds
				then = now;
			
				driver->beginScene(true, true, video::SColor(255, 113, 113, 133));

				driver->beginScene(true, true, video::SColor(0, 200, 200, 200));
				smgr->drawAll();
				if (appReceiver.isKeyDown(KEY_ESCAPE))
				{
					device->closeDevice();
				}

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

