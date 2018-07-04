#pragma once
#ifndef TUTORIALSTATE_H
#define TUTORIALSTATE_H

#include "GameStates.h"
#include "GamePlayState.h"
#include "Timer.h"
#include "Opponent.h"
#include  "PlaceObjects.h"
#include "Player.h"
#include "TurretAI.h" 
#include "GUIBase.h"
#include <memory>
#include "Observer.h"
#include "spriteAnimation.h"

class TutorialState : public CGameState
{
public:
	TutorialState();

	static TutorialState* Instance();

	virtual void Init(CGameManager* pManager);

	virtual void Clear(CGameManager* pManager);

	virtual void Update(CGameManager* pManager);

	virtual void KeyboardEvent(CGameManager* pManager);

	virtual void MouseEvent(CGameManager* pManager);

	void TutorialCompleted();

	~TutorialState();

private:
	static TutorialState m_TutorialState;

	ISoundEngine * soundEngine;
	PlaceObjects* PoManager;

	Timer* timer;
	Timer* walkTimer;
	Player* player;
	Opponent* opponent;
	IMeshSceneNode* gunNode;
	Grid* grid;
	Observer* observer;
	vector<TurretAI*> turretList;

	CurrencyUI* currencyUI;
	Reticle* playerReticle;
	PlayerHealth* playerHealth;
	DrawUI * drawUI;
	Tutorial* tutorial;

	//necessary managers
	EnemyManager* enemyManager;
	WaveManager* waveManager;
	Currency* cManager;
	PlayerBase* playerCore;

	ISceneNode* particleDing;

	bool isReadyToShoot;
	bool isBuildPhase;
	int delayBetweenShots = 500;

	Listener* shootListener;
	Listener* walkListener;
	Listener* killEnemyListener;
	Listener* spawnObstacleListener;
	Listener* spawnTurretListener;

	bool walkingState = false;
	bool tutorialFinished = false;
	SpriteAnimation* spriteAnim;
	Timer * tutEndTimer;
};
#endif