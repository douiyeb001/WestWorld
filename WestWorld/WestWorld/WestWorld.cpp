#include <irrlicht.h>
#include "driverChoice.h"
#include "CAppReceiver.h"
#include "Player.h"


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

	IrrlichtDevice * device = createDevice(EDT_OPENGL,
		core::dimension2d<u32>(640, 480), 16, false, false, false, &appReceiver);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Load .irr file example");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	Player player(smgr);
	// load the scene
	if (argc > 1)
		smgr->loadScene(argv[1]);
	else
		smgr->loadScene("scene/TesttRaayy.irr");


	device->getCursorControl()->setVisible(false);
	///Variables needed for Ray
	scene::ITriangleSelector* selector = 0;

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

	int lastFPS = -1;

	// draw the selection triangle only as wireframe


	u32 then = device->getTimer()->getTime();
	while (device->run())
		if (device->isWindowActive())
		{
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 10.f; // Time in seconds
			then = now;

			driver->beginScene(true, true, video::SColor(255, 113, 113, 133));

			driver->beginScene(true, true, video::SColor(0, 200, 200, 200));

			//RayCast Draw
			// Unlight any currently highlighted scene node
			
			

			player.RayCreate(smgr, driver, selector, meta, player.getCamera(), device);

		
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

