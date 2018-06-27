#include "Player.h"

using namespace std;

float shootingDistance = 1000.0f;
	
Player::Player(ISceneManager* smgr,IVideoDriver* driver, ISceneNodeAnimator* anim, IMetaTriangleSelector* meta) {
	//pSmgr = smgr;
	// create new player
	CreatePlayer(smgr, meta);
	health = 5;

}

Player::~Player() {
	// destructor
	anim->drop();
}


void Player::HandleMovement() {
}

void Player::CreatePlayer(ISceneManager* smgr, IMetaTriangleSelector* meta) {

	SKeyMap pKeyMap[5];
	//! Sets the Keymap for the FPS camera node
	//! keycodes for movement are set to the corresponding action
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


	//! 
	cameraNode = smgr->addCameraSceneNodeFPS(0, 80.0f, 0.2f, -1, pKeyMap, 8, true, .4);
	cameraNode->setPosition(vector3df(20,20,450));
	anim = smgr->createCollisionResponseAnimator(meta, cameraNode, vector3df(15, 15, 15), vector3df(0, -1, 0));
	//meta->drop();
	cameraNode->addAnimator(anim);
	
	//anim->drop();
	//anim(cameraNode);
	//anim = m_pSceneManager->createCollisionResponseAnimator(meta, cam, vector3df(15, 15, 15), vector3df(0, -1, 0));
	//pManager->SetCollision();
	//cameraNode->addAnimator(pManager->GetAnim()); // problem here when deleting
	
	//collision response            
	
}
ICameraSceneNode* Player::getCamera() {
	return cameraNode;
}

ISceneNode* Player::RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode* pPlayer, ISceneManager* smgr,ISceneNode* gun)
{
	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	//! Add it to the meta selector, which will take a reference to it
	pMeta->addTriangleSelector(pSelector);

	ray.start = pPlayer->getPosition();
	//! end of the ray will be at the end of the direction the camera is facing
	ray.end = ray.start + (pPlayer->getTarget() - ray.start).normalize() * shootingDistance;

	ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle,
			17,0);


	// create line for shooting
	vector3df start = pPlayer->getPosition();
	vector3df end = (pPlayer->getTarget() - start);
	end.normalize();
	start += end * 40.0f;
	end = start + (end * pPlayer->getFarValue());
	line3d<f32> line(start, end);


	vector3df FlareStart = vector3df(pPlayer->getPosition().X-20, pPlayer->getPosition().Y, pPlayer->getPosition().Z);
	//! local ISceneNode, needed for getCollisionPoint method
	ISceneNode* testNode;
	//! if the ray collides with an object it will return the normal of the triangle and it will set
	//! the end of the line to the position it hit)
	if (collMan->getCollisionPoint(line, pMeta, end, hitTriangle, testNode)) {
		vector3df out = hitTriangle.getNormal();
		OnShoot(end, smgr);
		out.setLength(0.03f);
	}
	//! In case the ray doesn't hit anything the end of the line will be set to the far value of the player camera
	else {
		vector3df start = pPlayer->getPosition();

		vector3df end = (pPlayer->getTarget() - start);
		end.normalize();
		start += end * 20.0f;
		end = start + (end * pPlayer->getFarValue());
	}

	//! creates a new node that will alway face the player
	//! The material of the node will be
	ISceneNode* node = 0;
	ISceneNode* flashNode = 0;
	node = smgr->addBillboardSceneNode(0, dimension2d<f32>(10, 10), start);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("textures/fx/sprites/redparticle.bmp"));
	node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	//For Gun flare	
	flashNode = smgr->addBillboardSceneNode(gun,dimension2d<f32>(10, 10), vector3df( gun->getPosition().X, gun->getPosition().Y, gun->getPosition().Z+100));
	flashNode->setMaterialFlag(EMF_LIGHTING, false);
	flashNode->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("textures/fx/sprites/muzzleFlash.png"));
	flashNode->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	flashNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	//! Length of flight
	const auto length = (f32)(end - start).getLength();
	const auto speed = 0.8f;
	const auto time = (u32)(length / speed);


	//! create a fly straight animator for the bullet
	//! add a delete animator  that will delete the animated bullet
	//! at the end of its lifecycle
	//animator for bullet
	ISceneNodeAnimator* anim = 0;
	ISceneNodeAnimator* flashAnim = 0;
	anim = smgr->createFlyStraightAnimator(start, end, time);

	flashAnim = smgr->createFlyStraightAnimator(vector3df(gun->getPosition().X, gun->getPosition().Y+5, gun->getPosition().Z + 5), vector3df(gun->getPosition().X, gun->getPosition().Y +5, gun->getPosition().Z + 5), 200);

	node->addAnimator(anim);
	flashNode->addAnimator(flashAnim);

	anim = smgr->createDeleteAnimator(time);

	flashAnim = smgr->createDeleteAnimator(200);
	flashNode->addAnimator(flashAnim);
	node->addAnimator(anim);

	
	anim->drop();
	//flare anim
	


	//! returns a scene node if the raycasting collided with one
	if (selectedSceneNode) {
		return selectedSceneNode;
	} else {
		return NULL;
	}
}

void Player::OnShoot(vector3df placeHit, ISceneManager* smgr) {
	// on the place hit create a bloodspatter
	ISceneNode* node = 0;
	node = smgr->addBillboardSceneNode(0, dimension2d<f32>(10, 10), placeHit);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("textures/fx/sprites/redparticle.bmp"));
	node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	ISceneNodeAnimator* anim = 0;

	node->addAnimator(anim);
//	anim->drop();
	anim = smgr->createDeleteAnimator(300);
	node->addAnimator(anim);
	//anim->drop();
}

void Player::Damaged(int damage) {
	health -= damage;

	if (health <= 0) {

		health = 0;
	}
}

irr::core::vector3df Player::GetPosition() {
	return cameraNode->getAbsolutePosition();
}