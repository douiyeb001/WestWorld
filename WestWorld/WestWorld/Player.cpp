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
	ICameraSceneNode *  camera = smgr->addCameraSceneNodeFPS(0, 80.0f, movementSpeed, -1, keyMap, 8, true, .4);
}


