#pragma once
#include <irrlicht.h>
#include "HealthBar.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

class PlayerBase
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="base">	[in,out] If non-null, the base. </param>
	/// <param name="mgr"> 	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PlayerBase(scene::ISceneNode* base, scene::ISceneManager* mgr);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~PlayerBase();
	/// <summary>	The base. </summary>
	scene::ISceneNode* base;
	/// <summary>	The health. </summary>
	int health;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the health. </summary>
	///
	/// <value>	The health. </value>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	//int* rHealth = &health;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Despawns this object. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Despawn();   

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Damaged. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="damage">	The damage. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Damaged(int damage);
	/// <summary>	= new HealthBar((smgr->getRootSceneNode(), smgr, 666)) </summary>
	//HealthBar *healthBar;
};