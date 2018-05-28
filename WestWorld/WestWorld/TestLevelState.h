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
#include "EnemySpawner.h"
#include <vector>
#include "EnemyManager.h"
#include "PauseManager.h"
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
	/// <summary>	If you can shoot or not. </summary>
	bool readyToShoot = true;
	/// <summary>	The builiding phase. </summary>
	bool isBuildPhase;
	/// <summary>	The wave count. </summary>
	int waveCount = 0;

	/// <summary>	The camera node. </summary>
	//ICameraSceneNode* cameraNode;
	/// <summary>	The healthbar. </summary>
	//std::unique_ptr<PlayerHealthBar> healthbar;
	PlayerHealthBar* healthbar;
	/// <summary>	The UI for the currency. </summary>
	CurrencyUI* currencyUI;
	/// <summary>	The player reticle. </summary>
	Reticle* playerReticle;
	/// <summary>	The manager for placing objects. </summary>
	PlaceObjects* PoManager;
	/// <summary>	The victory screen. </summary>
	VictoryScreen* pVictory;
	
	/// <summary>	The player. </summary>
	std::unique_ptr<Player> pPLayer;
	/// <summary>	The manager for the currency. </summary>
	Currency* cManager;
	
	TurretAI* pTurretAI;
	/// <summary>	The AI of the turrets. </summary>
	PlayerBase* playerCore;
	/// <summary>	The enemy spawn point. </summary>
	EnemySpawner* spawnPoint;
	/// <summary>	The manager for pausing the game. </summary>
	PauseManager* pauseManager;
	/// <summary>	The manager for the enemies. </summary>
	EnemyManager* enemyManager;
	/// <summary>	The game over screen. </summary>
	GameOverScreen* pGameOver;
	//Objective* pObjective;
	/// <summary>	Draws the UI onto the screen. </summary>
	DrawUI * pDrawUI;
	/// <summary>	The UI for the wave counter. </summary>
	WaveCounterUI* pWaveCounterUI;
	/// <summary>	The test level. </summary>
	static TestLevelState  m_TestLevelState;
	/// <summary>	. </summary>
	/// <summary>	The obstacles. </summary>
	std::vector<bool> obstacles;
	
};
#endif