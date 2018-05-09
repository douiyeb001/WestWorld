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
	ITriangleSelector* selector = 0;
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
	
	//collision response            
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		selector, cameraNode, core::vector3df(30, 50, 30), //<----Elipsoid value
		core::vector3df(0, -0.1, 0),vector3df(0, 50, 0));
	cameraNode->addAnimator(anim);
	anim->drop();
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

	scene::ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle,
			17,0);


	//create line for shooting
	vector3df start = pPlayer->getPosition();
	vector3df end = (pPlayer->getTarget() - start);
	end.normalize();
	start += end * 20.0f;
	end = start + (end * pPlayer->getFarValue());
	line3d<f32> line(start, end);

	ISceneNode* test;
	if (collMan->getCollisionPoint(line, pMeta, end, hitTriangle, test)) {
		vector3df out = hitTriangle.getNormal();
		out.setLength(0.03f);
	}
	else {
		vector3df start = pPlayer->getPosition();

		vector3df end = (pPlayer->getTarget() - start);
		end.normalize();
		start += end * 20.0f;
		end = start + (end * pPlayer->getFarValue());
	}


	ISceneNode* node = 0;
	node = smgr->addBillboardSceneNode(0, dimension2d<f32>(10, 10), start);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("textures/fx/sprites/redparticle.bmp"));
	node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	f32 length = (f32)(end - start).getLength();
	const f32 speed = 0.8f;
	u32 time = (u32)(length / speed);

	ISceneNodeAnimator* anim = 0;

	// set flight line

	anim = smgr->createFlyStraightAnimator(start, end, time);
	node->addAnimator(anim);
	anim->drop();
	anim = smgr->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();

	if (selectedSceneNode) {
		//	//printf(selectedSceneNode->getDebugName());
		//	//selectedSceneNode->setPosition(vector3df(10, 10, 10));
		//	//pMeta->removeTriangleSelector(selectedSceneNode->getTriangleSelector());
		//		//selectedSceneNode->remove();
		//	return selectedSceneNode;
		//}
		//selectedSceneNode->setPosition(vector3d());
	
		return selectedSceneNode;
	} 
}

void Player::OnShoot(vector3df start, vector3df end, ISceneNode* hitNode, ISceneManager* smgr) {
	// create fire ball

}