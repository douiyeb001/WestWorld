
#include <irrlicht.h>
#include "driverChoice.h"
//#include "IEventReceiver.h"
#include "MouseInput.h"
#include "IMesh.h"
#include "IDFLAGS.h"
#include "PlaceObjects.h"


using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

bool hasSpawnedTurret;





int main(int argc, char** argv)
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;


	MouseInput mouseInput;

	// create device and exit if creation failed

	IrrlichtDevice* device =
		createDevice(driverType, core::dimension2d<u32>(640, 480), 16, false, false, false, &mouseInput);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Load .irr file example");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	PlaceObjects po;
	// load the scene
	if (argc > 1)
		smgr->loadScene(argv[1]);
	else
		smgr->loadScene("scene/T_Placing.irr");

	scene::ICameraSceneNode * camera = smgr->addCameraSceneNodeFPS(0, 50.f, 0.1f);

	// Create a meta triangle selector to hold several triangle selectors.
	scene::ITriangleSelector * selector = 0;
	scene::IMetaTriangleSelector * meta = smgr->createMetaTriangleSelector();
	core::array<scene::ISceneNode *> nodes;
	smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

	for (u32 i = 0; i < nodes.size(); ++i)
	{
		scene::ISceneNode * node = nodes[i];
		

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
	//meta->drop(); // I'm done with the meta selector now

	camera->addAnimator(anim);
	anim->drop(); // I'm done with the animator now

				  // And set the camera position so that it doesn't start off stuck in the geometry
	camera->setPosition(core::vector3df(0.f, 20.f, 0.f));


	device->getCursorControl()->setVisible(false);

	//// Point the camera at the cube node, by finding the first node of type ESNT_CUBE
	//scene::ISceneNode * cube = smgr->getSceneNodeFromType(scene::ESNT_CUBE);
	//if (cube)
	//	camera->setTarget(cube->getAbsolutePosition());

	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();

	int lastFPS = -1;

	while (device->run())
		if (device->isWindowActive())
		{
			

			driver->beginScene(true, true, video::SColor(0, 200, 200, 200));
			smgr->drawAll();


			// All intersections in this example are done with a ray cast out from the camera to
			// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
			// trajectory or a sword's position, or create a ray from a mouse click position using
			// ISceneCollisionManager::getRayFromScreenCoordinates()
			core::line3d<f32> ray;
			ray.start = camera->getPosition();
			ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 100.0f;

			// Tracks the current intersection point with the level or a mesh
			core::vector3df intersection;
			// Used to show with triangle has been hit
			core::triangle3df hitTriangle;

			scene::ISceneNode * collidedObject;

			// This call is all you need to perform ray/triangle collision on every scene node
			// that has a triangle selector, including the Quake level mesh.  It finds the nearest
			// collision point/triangle, and returns the scene node containing that point.
			// Irrlicht provides other types of selection, including ray/triangle selector,
			// ray/box and ellipse/triangle selector, plus associated helpers.
			// See the methods of ISceneCollisionManager

			//scene::ISceneNode * selectedSceneNode =
			//	collMan->getSceneNodeAndCollisionPointFromRay(
			//		ray,
			//		intersection, // This will be the position of the collision					
			//		hitTriangle, // This will be the triangle hit in the collision
			//		IDFlag::spawnGround, // This ensures that only nodes that we have
			//						   // set up to be pickable are considered
			//		0); // Check the entire scene (this is actually the implicit default)

			if (collMan->getCollisionPoint(
				ray, meta, intersection, hitTriangle, collidedObject)) {
				if (collidedObject->getID() == IDFlag::spawnGround)
				{
					if (mouseInput.GetMouseState().isLeftButtonDown)
					{
						if (!hasSpawnedTurret)
						{
							po.SpawnTurret(driver, smgr, intersection, selector, meta, IDFlag::spawnedObject);
							po.CreateCollision(anim, smgr, camera, meta);
							hasSpawnedTurret = true;
						}
					}
					else if (!mouseInput.GetMouseState().isLeftButtonDown)
					{
						hasSpawnedTurret = false;
					}
				}
				
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
