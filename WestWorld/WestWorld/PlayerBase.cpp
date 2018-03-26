#include "PlayerBase.h"
#include <irrlicht.h>

using namespace irr;



PlayerBase::PlayerBase(scene::ISceneNode* node, scene::ISceneManager* mgr)
{
	base = node;
	healthBar = new HealthBar(node, mgr, 666);
	healthBar->setPosition(irr::core::vector3df(50, 1100, 0));
	healthBar->setScale(irr::core::vector3df(20, 20, 20));
	healthBar->setRotation(irr::core::vector3df(0, 180, 0));
	healthBar->SetHealth(*rHealth);
}


PlayerBase::~PlayerBase()
{
}


void PlayerBase::Despawn() {
	//base->setVisible(false);
}

void PlayerBase::Damaged(int damage) {
	*rHealth -= damage;
	if (*rHealth <= 0) {
		Despawn();
		*rHealth = 0;
	}
	healthBar->SetHealth(*rHealth);
}