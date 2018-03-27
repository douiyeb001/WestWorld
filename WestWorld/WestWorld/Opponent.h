#pragma once
#include <irrlicht.h>
#include "PlayerBase.h"

using namespace irr;

class Opponent
{
public:
	Opponent(scene::ISceneNode* enemy);
	~Opponent();
	scene::ISceneNode* enemy;
	bool active;

	bool collidesWith(scene::ISceneNode* ground);
	void collidesWithTarget(PlayerBase target);
	void Despawn();
	void Damage(PlayerBase target);
};