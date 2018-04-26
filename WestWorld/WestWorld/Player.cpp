#include "Player.h"
#include <iostream>

using namespace std;
	
Player::Player(ISceneManager* smgr,IVideoDriver* driver, ISceneNodeAnimator* anim) {
	// constructor
	pDriver = driver;
	//pSmgr = smgr;
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
	cameraNode->setPosition(vector3df(20,20,450));
	

}
ICameraSceneNode* Player::getCamera() {
	return cameraNode;
}

ISceneNode* Player::RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode* pPlayer, ISceneManager* smgr)
{
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	// Add it to the meta selector, which will take a reference to it
	pMeta->addTriangleSelector(pSelector);
	// And drop my reference to it, so that the meta selector owns it.

	ray.start = pPlayer->getPosition();
	ray.end = ray.start + (pPlayer->getTarget() - ray.start).normalize() * 100.0f;
//	OnShoot(pPlayer->getPosition(), ray.end);
	scene::ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle,
			17,0);

	//create line for shooting


	//start timer

	if (selectedSceneNode) {
		//printf(selectedSceneNode->getDebugName());
		//selectedSceneNode->setPosition(vector3df(10, 10, 10));
		//pMeta->removeTriangleSelector(selectedSceneNode->getTriangleSelector());
			//selectedSceneNode->remove();
		return selectedSceneNode;
	}
	//selectedSceneNode->setPosition(vector3d());
}

void Player::OnShoot(vector3df start, vector3df end) {
	// timer start, draw line
	SColor color = SColor(100, 255, 255, 255);
	SMaterial m;
	m.Lighting = false;
	//->getVideoDriver()->setMaterial(m);
	pDriver->setMaterial(m);
	pDriver->setTransform(video::ETS_WORLD, core::matrix4());
	pDriver->draw3DLine(start, end, color);
}