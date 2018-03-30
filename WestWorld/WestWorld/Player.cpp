#include "Player.h"
#include <iostream>

using namespace std;
	
Player::Player(ISceneManager* smgr,IVideoDriver* driver, ISceneNodeAnimator* anim) {
	// constructor
	pDriver = driver;
	pSmgr = smgr;
	pAnim = anim;
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
void Player::RayCreate(ISceneManager* smgr, scene::ISceneCollisionManager *collMan, ICameraSceneNode* pPlayer, scene::IMetaTriangleSelector *meta)
{				
				core::line3d<f32> ray;
				ray.start = pPlayer->getPosition();
				ray.end = ray.start + (pPlayer->getTarget() - ray.start).normalize() * 50.0f;

				// Tracks the current intersection point with the level or a mesh
				ISceneNode* selectedSceneNode =
					collMan->getSceneNodeAndCollisionPointFromRay(
						ray,
						intersection, // This will be the position of the collision
						hitTriangle, // This will be the triangle hit in the collision
						15, // This ensures that only nodes that we have
										   // set up to be pickable are considered
						0); // Check the entire scene (this is actually the implicit default)
				if (selectedSceneNode) {
					smgr->addToDeletionQueue(selectedSceneNode);
					meta->removeTriangleSelector(selectedSceneNode->getTriangleSelector());
					selectedSceneNode = 0;
				}
	}



