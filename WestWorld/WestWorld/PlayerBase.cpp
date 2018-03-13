#include "PlayerBase.h"
#include <irrlicht.h>

using namespace irr;



PlayerBase::PlayerBase(scene::ISceneNode* node)
{
	base = node;
}


PlayerBase::~PlayerBase()
{
}


void PlayerBase::Despawn() {
	base->setVisible(false);
}

void PlayerBase::Damaged(int damage) {
	health -= damage;
	if (health <= 0)
		Despawn();
}