#pragma once
#ifndef EnemyManager_H
#define EnemyManager_H

#include <irrlicht.h>
#include <list>
//#include <vector>

using namespace std;
using namespace irr;

class EnemyManager 
{
public:
	EnemyManager();
	void CheckCollision(scene::ISceneNode* collidedObject);
	void FillList(scene::ISceneManager* smgr);
	~EnemyManager();
	list<scene::ISceneNode*> test;
};

#endif