#pragma once
#include <irrlicht.h>
#include "HealthBar.h"

using namespace irr;

class PlayerBase
{
public:
	PlayerBase(scene::ISceneNode* base, scene::ISceneManager* mgr);
	~PlayerBase();
	scene::ISceneNode* base;
	int health = 1;
	int* rHealth = &health;
	void Despawn();   
	void Damaged(int damage);
	HealthBar *healthBar;// = new HealthBar((smgr->getRootSceneNode(), smgr, 666))
};