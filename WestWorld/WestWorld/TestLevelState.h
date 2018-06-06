#pragma once
#ifndef TestLevelState_H
#define TestLevelState_H

#include "GamePlayState.h"
#include "GUIBase.h"
#include "PlaceObjects.h" 
#include "Currency.h"
#include "Player.h"
#include "Opponent.h"
#include "TurretAI.h"
#include "AStar.h"
#include "EnemySpawner.h"
#include <vector>
#include "EnemyManager.h"
#include "Timer.h"
#include "PauseManager.h"
#include "WaveManager.h"
#include <memory>

class TestLevelState : public CGamePlayState {

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Initializes this object. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Init(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clears this object to its blank/initial state. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Clear(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates the given pManager. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Update(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Keyboard event. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void KeyboardEvent(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Mouse event. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void MouseEvent(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the instance. </summary>
	///
	/// <returns>	Null if it fails, else a pointer to a TestLevelState. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static TestLevelState* Instance();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual ~TestLevelState();

protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	TestLevelState();

private:

	//Timer *p_Timer;
	bool readyToShoot = true;
	bool isBuildPhase;

	/// <summary>	The camera node. </summary>
	//ICameraSceneNode* cameraNode;
	/// <summary>	The healthbar. </summary>
	//std::unique_ptr<PlayerCore> healthbar;
	PlayerCore* healthbar;
	/// <summary>	Manager for po. </summary>
	CurrencyUI* currencyUI;
	Reticle* playerReticle;
	PlayerHealth* pPlayerHealth;
	PlaceObjects* PoManager;
	VictoryScreen* pVictory;
	ISoundEngine* soundEngine;
	
	/// <summary>	The player. </summary>
	std::unique_ptr<Player> pPLayer;
	Currency* cManager;
	
	TurretAI* pTurretAI;
	/// <summary>	The player core. </summary>
	PlayerBase* playerCore;
	/// <summary>	State of the test level. </summary>
	IMeshSceneNode* gunNode;
	WaveManager* waveManager;
	PauseManager* pauseManager;
	EnemyManager* enemyManager;
	GameOverScreen* pGameOver;
	//Objective* pObjective;
	DrawUI * pDrawUI;
	WaveCounterUI* pWaveCounterUI;
	static TestLevelState  m_TestLevelState;
	/// <summary>	. </summary>
	//std::vector<bool> obstacles;
	Grid* grid;
	vector<TurretAI*> turretList;
};
#endif