#pragma once
#ifndef EnemyManager_H
#define EnemyManager_H

#include <irrlicht.h>
#include <vector>
#include "Opponent.h" 
#include "Currency.h"
#include "Timer.h"
#include "IDamagable.h"
#include "GUIBase.h"


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
	Currency* cManager;

	EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver, Currency* cManager, Timer * pTimer);

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

	bool CheckCollision(scene::ISceneNode* collidedObject);
	vector<Opponent*> GiveArray();
	void FillList(Opponent* enemy);
	void Update(std::vector<GridCell*> PlayerRange, IDamagable* pPlayer);
	void RemoveFromArray(scene::ISceneNode* turrentOpponent);

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

	vector<Opponent*> opponentList;
	void UpdatePath(std::vector<GridCell*> newPath, GridCell* changedCell);
	Timer* p_Timer;
	
};
#endif



