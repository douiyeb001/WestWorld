#include "Player.h"

Player::Player(ISceneManager* smgr) {
	// constructor

	// create new player
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

	CreatePlayer(smgr, keyMap, MOVEMENT_SPEED);
}

Player::~Player() {
	// destructor
}

void Player::HandleMovement() {

}

void Player::CreatePlayer(ISceneManager* smgr, SKeyMap* keyMap, float movementSpeed) {
	cameraNode = smgr->addCameraSceneNodeFPS(0, 80.0f, movementSpeed, -1, keyMap, 8, true, .4);
	cameraNode->setPosition(vector3df(20,20,20));
}

ICameraSceneNode* Player::getCamera() {
	return cameraNode;
}


	//if (selector)
	//{
	//	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
	//		selector, camera, core::vector3df(30, 50, 30),
	//		core::vector3df(0, -10, 0), core::vector3df(0, 30, 0));
	//	selector->drop(); // As soon as we're done with the selector, drop it.
	//	camera->addAnimator(anim);
	//	anim->drop();  // And likewise, drop the animator when we're done referring to it.
	//}
//
//scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
//	meta, camera, core::vector3df(5, 5, 5),
//	core::vector3df(0, -.981f, 0));
//meta->drop(); // I'm done with the meta selector now
//camera->addAnimator(anim);
//anim->drop(); // I'm done with the animator now
