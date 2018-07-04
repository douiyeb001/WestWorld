#pragma once
#include <irrlicht.h>

class IDamagable {
public:
	virtual void Damaged(int damage) = 0;
	virtual irr::core::vector3df GetPosition() = 0;
	int health;
	bool isPlayer;
};