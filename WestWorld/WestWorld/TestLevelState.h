#pragma once
#ifndef TestLevelState_H
#define TestLevelState_H

#include "GamePlayState.h"
#include "GUIBase.h"
#include "PlaceObjects.h" 
#include "Player.h"
#include "IDFLAGS.h"
#include "Opponent.h"
#include "TurretAI.h"
#include "AStar.h"
#include "EnemySpawner.h"
#include <vector>
#include "EnemyManager.h"

class TestLevelState : public CGamePlayState {

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Initializes this object. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Init(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clears this object to its blank/initial state. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Clear(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates the given pManager. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Update(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Keyboard event. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void KeyboardEvent(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Mouse event. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void MouseEvent(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the instance. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <returns>	Null if it fails, else a pointer to a TestLevelState. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static TestLevelState* Instance();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual ~TestLevelState();

protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	TestLevelState();

private:
	/// <summary>	The title picture. </summary>
	ITexture * m_titlePic;
	/// <summary>	The camera node. </summary>
	ICameraSceneNode* cameraNode;
	/// <summary>	The healthbar. </summary>
	PlayerHealthBar* healthbar;
	/// <summary>	Manager for po. </summary>
	PlaceObjects* PoManager;
	/// <summary>	The p layer. </summary>
	Player* pPLayer; 
	/// <summary>	The enemy. </summary>
	TurretAI* pTurretAI;
	Opponent* enemy;
	/// <summary>	The player core. </summary>
	PlayerBase* playerCore;
	/// <summary>	State of the test level. </summary>
	EnemySpawner* spawnPoint;
	EnemyManager* enemyManager;
	static TestLevelState  m_TestLevelState;
	/// <summary>	. </summary>
	bool obstacles[(World_Size / Cell_Size)*(World_Size / Cell_Size)];
	std::vector<bool> obstacles;

};
#endif