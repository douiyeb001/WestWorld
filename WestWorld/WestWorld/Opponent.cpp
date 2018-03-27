#include "Opponent.h"
#include <irrlicht.h>

using namespace irr;
Opponent::Opponent(scene::ISceneNode* node)
{
	enemy = node;
	active = true;
}

Opponent::~Opponent()
{
}

bool Opponent::collidesWith(scene::ISceneNode* ground)
{
	//temp
	ground->updateAbsolutePosition();
	enemy->updateAbsolutePosition();
	return ground->getTransformedBoundingBox().intersectsWithBox(enemy->getTransformedBoundingBox());
}

void Opponent::collidesWithTarget(PlayerBase target)
{
	//temp
	target.base->updateAbsolutePosition();
	enemy->updateAbsolutePosition();
	if (target.base->getTransformedBoundingBox().intersectsWithBox(enemy->getTransformedBoundingBox()))
		target.Damaged(1);
}

void Opponent::Despawn() {
	active = false;
	enemy->setVisible(false);
}
