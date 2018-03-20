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
		core::dimension2d<u32>(640, 480), 16, false, false, false, &appReceiver);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Load .irr file example");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	// load the scene
	if (argc > 1)
		smgr->loadScene(argv[1]);
	else
		smgr->loadScene("scene/TestRay.irr");

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
	device->getCursorControl()->setVisible(false);
	///Variables needed for Ray
	scene::ITriangleSelector* selector = 0;
	// Add the billboard.
	scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, driver->getTexture("media/particle.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it



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

	scene::ISceneNode * ground = smgr->getSceneNodeFromName("Ground");

	scene::IMeshSceneNode* groundNode = 0;
	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");


	if (groundNode)
	{


		selector = smgr->createOctreeTriangleSelector(
			groundNode->getMesh(), groundNode, 128);
		groundNode->setTriangleSelector(selector);
		// We're not done with this selector yet, so don't drop it.
	}


	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		meta, camera, core::vector3df(5, 5, 5),
		core::vector3df(0, -.981f, 0));
	meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now

				  // And set the camera position so that it doesn't start off stuck in the geometry
	camera->setPosition(core::vector3df(0.f, 20.f, 0.f));

	//RaCast Stuff
	scene::IAnimatedMeshSceneNode* node = 0;
	video::SMaterial material;



	// Add an MD2 node, which uses vertex-based animation.
	node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/sydney.md2"),
		0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(10, 10, 100)); // Put its feet on the floor.
	node->setScale(core::vector3df(1.6f)); // Make it appear realistically scaled
	node->setMD2Animation(scene::EMAT_POINT);
	node->setAnimationSpeed(20.f);
	material.setTexture(0, driver->getTexture("media/sydney.bmp"));
	material.Lighting = true;
	material.NormalizeNormals = true;
	node->getMaterial(0) = material;

	// Now create a triangle selector for it.  The selector will know that it
	// is associated with an animated node, and will update itself as necessary.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop(); // We're done with this selector, so drop it now.



	material.setTexture(0, 0);
	material.Lighting = false;

	// Add a light, so that the unselected nodes aren't completely dark.
	scene::ILightSceneNode * light = smgr->addLightSceneNode(0, core::vector3df(-60, 100, 400),
		video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 600.0f);
	light->setID(ID_IsNotPickable); // Make it an invalid target for selection.

									// Remember which scene node is highlighted
	scene::ISceneNode* highlightedSceneNode = 0;
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	int lastFPS = -1;

	// draw the selection triangle only as wireframe
	material.Wireframe = true;


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
			if (highlightedSceneNode)
			{
				highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
				highlightedSceneNode = 0;

			}
			

			// All intersections in this example are done with a ray cast out from the camera to
			// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
			// trajectory or a sword's position, or create a ray from a mouse click position using
			//ISceneCollisionManager::getRayFromScreenCoordinates()
			core::line3d<f32> ray;
			ray.start = camera->getPosition();
			ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;
			ISceneNode * colObject;
			// Tracks the current intersection point with the level or a mesh
			core::vector3df intersection;
			// Used to show with triangle has been hit
			core::triangle3df hitTriangle;

			// This call is all you need to perform ray/triangle collision on every scene node
			// that has a triangle selector, including the Quake level mesh.  It finds the nearest
			// collision point/triangle, and returns the scene node containing that point.
			// Irrlicht provides other types of selection, including ray/triangle selector,
			// ray/box and ellipse/triangle selector, plus associated helpers.
			// See the methods of ISceneCollisionManager
			if (appReceiver.GetMouseState().LeftButtonDown)
			{
				device->closeDevice();
				node->remove();
			}
			if (collMan->getCollisionPoint(ray,meta,intersection,hitTriangle,colObject))
			{
				bill->setPosition(intersection);

				// We need to reset the transform before doing our own rendering.
				driver->setTransform(video::ETS_WORLD, core::matrix4());
				driver->setMaterial(material);
				driver->draw3DTriangle(hitTriangle, video::SColor(0, 255, 0, 0));
				
				// We can check the flags for the scene node that was hit to see if it should be
				// highlighted. The animated nodes can be highlighted, but not the Quake level mesh
				
			}
		
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

