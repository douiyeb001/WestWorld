#pragma once
#include <irrlicht.h>

using namespace irr;
class PlayerBase
{
public:
	PlayerBase(scene::ISceneNode* base);
	~PlayerBase();
	scene::ISceneNode* base;
	int health = 1;
	void Despawn();
	void Damaged(int damage);
};