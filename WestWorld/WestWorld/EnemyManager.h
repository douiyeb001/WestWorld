#pragma once
#ifndef EnemyManager_H
#define EnemyManager_H

#include <irrlicht.h>
#include <list>
#include <vector>
//#include <vector>

using namespace std;
using namespace irr;

class Enemy {
public:
	Enemy();
	~Enemy();
	void Init(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver);
	void Damage();
	int hp = 3;
	scene::IMeshSceneNode * node;
	scene::IMeshSceneNode * enemyNode(); // returns the node that belongs to a certain enemy
	scene::ISceneManager* ismgr;
	scene::ITriangleSelector* iselector;
	scene::IMetaTriangleSelector* imeta;
};

class EnemyManager 
{
public:
	scene::ISceneManager* ismgr;
	scene::ITriangleSelector* iselector;
	scene::IMetaTriangleSelector* imeta;
	video::IVideoDriver* idriver;

	EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver);
	void CreateEnemy();
	void CheckCollision(scene::ISceneNode* collidedObject);
	void FillList(Enemy* enemy);
	~EnemyManager();
	std::vector<Enemy*> enemyList;
};
#endif



