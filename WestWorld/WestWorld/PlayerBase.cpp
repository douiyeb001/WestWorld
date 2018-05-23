#include "PlayerBase.h"
#include <irrlicht.h>

using namespace irr;



PlayerBase::PlayerBase(scene::ISceneNode* node, scene::ISceneManager* mgr) : health(5)
{
	base = node;
	//healthBar = new HealthBar(node, mgr, 666);
	//HealthBar->setPosition(irr::core::vector3df(50, 1100, 0));
	//healthBar->setScale(irr::core::vector3df(20, 20, 20));
	//healthBar->setRotation(irr::core::vector3df(0, 180, 0));
	//healthBar->SetHealth(health);
}


PlayerBase::~PlayerBase()
{
}


void PlayerBase::Despawn() {
	//base->setVisible(false);
}

void PlayerBase::Damaged(int damage) {
	health -= damage;
	if (health <= 0) {
		Despawn();
		health = 0;
	}
	//healthBar->SetHealth(health);
}