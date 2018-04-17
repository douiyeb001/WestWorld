#include "Player.h"
#include <iostream>

using namespace std;
	
Player::Player(ISceneManager* smgr,IVideoDriver* driver) {
	// constructor
	pDriver = driver;
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
void Player::RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode* pPlayer, ISceneManager* smgr)
{
	
	core::line3d<f32> ray;
	ISceneNode * colObject;
	core::vector3df intersection;
	// Used to show with triangle has been hit
	core::triangle3df hitTriangle;

	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
		// Add it to the meta selector, which will take a reference to it
		pMeta->addTriangleSelector(pSelector);
		// And drop my reference to it, so that the meta selector owns it.
					
				ray.start = pPlayer->getPosition();
				ray.end = ray.start + (pPlayer->getTarget() - ray.start).normalize() * 10.0f;

				// Tracks the current intersection point with the level or a mesh
				scene::ISceneNode * selectedSceneNode =
					collMan->getSceneNodeAndCollisionPointFromRay(
						ray,
						intersection, // This will be the position of the collision
						hitTriangle,
						0);

				//selectedSceneNode->setPosition(vector3df(10, 10, 10));

  				if (selectedSceneNode) {

					//printf(selectedSceneNode->getDebugName());
					selectedSceneNode->setPosition(vector3df(10, 10, 10));
				//	selectedSceneNode->remove();
							}
				//selectedSceneNode->setPosition(vector3d());
			
	}



