#pragma once
#include <irrlicht.h>
#include "PlayerBase.h"
#include "AStar.h"

using namespace irr;

class Opponent
{
public:
	Opponent(scene::ISceneNode* node, scene::ISceneNode* _ground, PlayerBase* playerCore, bool obstacles[]);
	~Opponent();
	scene::ISceneNode* enemy;
	PlayerBase* target;
	bool active;
	float speed;
	scene::ISceneNode* ground;
	bool collidesWith(scene::ISceneNode* ground);
	void collidesWithTarget(PlayerBase target);
	void Despawn();
	void Damage(PlayerBase target);
	void Update();
	AStar pathfind;
};