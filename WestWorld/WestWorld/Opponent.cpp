#include "Opponent.h"
#include <irrlicht.h>

using namespace irr;
Opponent::Opponent(scene::ISceneNode* node, scene::ISceneNode* _ground, PlayerBase* playerCore, bool obstacles[(World_Size / Cell_Size)*(World_Size / Cell_Size)]) 
	: enemy(node), target(playerCore), ground(_ground), active(true), speed(0.1), pathfind(AStar(enemy, (*playerCore).base, obstacles))
{

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

void Opponent::Update() {
	enemy->setPosition(pathfind.NextPathPosition(enemy->getAbsolutePosition(), speed));
	collidesWithTarget(*target);

	while (collidesWith(ground))
		enemy->setPosition(enemy->getPosition() + core::vector3df(0, 0.001f, 0));
}