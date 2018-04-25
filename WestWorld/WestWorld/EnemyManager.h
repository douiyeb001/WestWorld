#pragma once
#ifndef EnemyManager_H
#define EnemyManager_H

#include <irrlicht.h>
//#include <list>
#include <vector>
#include "Opponent.h" 
//#include <vector>


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: std
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for enemies. </summary>
///
////////////////////////////////////////////////////////////////////////////////////////////////////

class EnemyManager 
{
public:
	scene::ISceneManager* ismgr;
	scene::ITriangleSelector* iselector;
	scene::IMetaTriangleSelector* imeta;
	video::IVideoDriver* idriver;

	EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	EnemyManager();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Check collision. </summary>
	///
	///
	/// <param name="collidedObject">	[in,out] If non-null, the collided object. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void CheckCollision(scene::ISceneNode* collidedObject);
	void FillList(Opponent* enemy);
	void Update();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Fill list. </summary>
	///
	///
	/// <param name="smgr">	[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void FillList(scene::ISceneManager* smgr);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~EnemyManager();

	std::vector<Opponent*> opponentList;


	
	/// <summary>	The test. </summary>
	list<scene::ISceneNode*> test;
};
#endif



