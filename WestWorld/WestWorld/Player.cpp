#include "Player.h"
#include <iostream>

using namespace std;
	
Player::Player(ISceneManager* smgr,IVideoDriver* driver) {
	// constructor
	pDriver = driver;
	pSmgr = smgr;
	// create new player
	
	
	CreatePlayer(smgr);

}

Player::~Player() {
	// destructor
}


void Player::HandleMovement() {
	
}

void Player::CreatePlayer(ISceneManager* smgr) {
	SKeyMap pKeyMap[9];

	pKeyMap[0].Action = EKA_MOVE_FORWARD;
	pKeyMap[0].KeyCode = KEY_KEY_W;

	pKeyMap[1].Action = EKA_MOVE_BACKWARD;
	pKeyMap[1].KeyCode = KEY_KEY_S;

	pKeyMap[2].Action = EKA_STRAFE_LEFT;
	pKeyMap[2].KeyCode = KEY_KEY_A;

	pKeyMap[3].Action = EKA_STRAFE_RIGHT;
	pKeyMap[3].KeyCode = KEY_KEY_D;

	pKeyMap[4].Action = EKA_JUMP_UP;
	pKeyMap[4].KeyCode = KEY_SPACE;

	cameraNode = smgr->addCameraSceneNodeFPS(0, 80.0f, 0.2f, -1, pKeyMap, 8, true, .4);
	cameraNode->setPosition(vector3df(20,20,20));
	

}
ICameraSceneNode* Player::getCamera() {
	return cameraNode;
}
void Player::RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode* pPlayer)
{
	
	core::line3d<f32> ray;
	ISceneNode * colObject;
	ICameraSceneNode* playerCamera = pPlayer;
	core::vector3df intersection;
	// Used to show with triangle has been hit
	core::triangle3df hitTriangle;
	
	// Add the billboard.
	scene::IBillboardSceneNode * bill = pSmgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setSize(core::dimension2d<f32>(0, 0));
	bill->setID(0); // This ensures that we don't accidentally ray-pick it
	scene::ISceneCollisionManager* collMan = pSmgr->getSceneCollisionManager();
		// Add it to the meta selector, which will take a reference to it
		pMeta->addTriangleSelector(pSelector);
		// And drop my reference to it, so that the meta selector owns it.
					
				bill->setPosition(vector3df(20,20,20));
				ray.start = playerCamera->getPosition();
				ray.end = ray.start + (playerCamera->getTarget() - ray.start).normalize() * 10.0f;

				// Tracks the current intersection point with the level or a mesh
				
				if (collMan->getCollisionPoint(ray, pMeta, intersection, hitTriangle, colObject))
				{
					pSmgr->addToDeletionQueue(colObject);
					// We need to reset the transform before doing our own rendering.
					pDriver->setTransform(video::ETS_WORLD, core::matrix4());

					// We can check the flags for the scene node that was hit to see if it should be
					// highlighted. The animated nodes can be highlighted, but not the Quake level mesh
					
				}
			
	}



