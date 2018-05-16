#include "PlayerBase.h"
#include <irrlicht.h>
#include"GameManager.h"




PlayerBase::PlayerBase(scene::ISceneNode* node, ISceneManager* mgr,IrrlichtDevice* pDevice) : health(5)
{
	base = node;
	_pDevice = pDevice;
	//healthBar = new HealthBar(node, mgr, 666);
	//HealthBar->setPosition(irr::core::vector3df(50, 1100, 0));
	//healthBar->setScale(irr::core::vector3df(20, 20, 20));
	//healthBar->setRotation(irr::core::vector3df(0, 180, 0));
	//healthBar->SetHealth(health);
}


PlayerBase::~PlayerBase()
{
}
	


void PlayerBase::Damaged(int damage, video::IVideoDriver * driver) {
	health -= damage;

	if (health <= 0) {

		health = 0;
	}
}