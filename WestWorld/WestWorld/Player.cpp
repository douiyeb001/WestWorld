#include "Player.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: std
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="smgr">  	[in,out] If non-null, the smgr. </param>
/// <param name="driver">	[in,out] If non-null, the driver. </param>
/// <param name="anim">  	[in,out] If non-null, the animation. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Player::Player(ISceneManager* smgr,IVideoDriver* driver, ISceneNodeAnimator* anim) {
	// constructor
	pDriver = driver;
	//pSmgr = smgr;
	// create new player
	CreatePlayer(smgr);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

Player::~Player() {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Handles the movement. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::HandleMovement() {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates a player. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="smgr">	[in,out] If non-null, the smgr. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the camera. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the camera. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

ICameraSceneNode* Player::getCamera() {
	return cameraNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Ray create. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pSelector">	[in,out] If non-null, the selector. </param>
/// <param name="pMeta">		[in,out] If non-null, the meta. </param>
/// <param name="pPlayer">  	[in,out] If non-null, the player. </param>
/// <param name="smgr">			[in,out] If non-null, the smgr. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode* pPlayer, ISceneManager* smgr)
{
	/// <summary>	Manager for collection. </summary>
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Add it to the meta selector, which will take a reference to it. And drop my reference to it, so that the meta selector owns it. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pSelector">	The first parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	pMeta->addTriangleSelector(pSelector);

	ray.start = pPlayer->getPosition();
	ray.end = ray.start + (pPlayer->getTarget() - ray.start).normalize() * 10.0f;
	scene::ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle,
			0);

	//selectedSceneNode->setPosition(vector3df(10, 10, 10));

	if (selectedSceneNode) {

		//printf(selectedSceneNode->getDebugName());
		//selectedSceneNode->setPosition(vector3df(10, 10, 10));
		pMeta->removeTriangleSelector(selectedSceneNode->getTriangleSelector());
			selectedSceneNode->remove();
	}
	//selectedSceneNode->setPosition(vector3d());
}