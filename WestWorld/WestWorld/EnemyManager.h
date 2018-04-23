#pragma once
#ifndef EnemyManager_H
#define EnemyManager_H

#include <irrlicht.h>
//#include <list>
#include <vector>
#include "Opponent.h" 
//#include <vector>

using namespace std;
using namespace irr;


class EnemyManager 
{
public:
	scene::ISceneManager* ismgr;
	scene::ITriangleSelector* iselector;
	scene::IMetaTriangleSelector* imeta;
	video::IVideoDriver* idriver;

	EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver);
	void CheckCollision(scene::ISceneNode* collidedObject);
	void FillList(Opponent* enemy);
	void Update();
	~EnemyManager();

	std::vector<Opponent*> opponentList;


	
};
#endif



