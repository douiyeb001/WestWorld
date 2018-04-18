#pragma once
#ifndef TestLevelState_H
#define TestLevelState_H

#include "GamePlayState.h"
#include "GUIBase.h"
#include "PlaceObjects.h" 
#include "Player.h"
#include "IDFLAGS.h"
#include "Opponent.h"
#include "AStar.h"
#include <vector>
#include "EnemyManager.h"

class TestLevelState : public CGamePlayState {

public:
	virtual void Init(CGameManager* pManager);
	virtual void Clear(CGameManager* pManager);
	virtual void Update(CGameManager* pManager);
	virtual void KeyboardEvent(CGameManager* pManager);
	virtual void MouseEvent(CGameManager* pManager);

	static TestLevelState* Instance();
	virtual ~TestLevelState();

protected:
	TestLevelState();

private:
	ITexture * m_titlePic;
	ICameraSceneNode* cameraNode;
	PlayerHealthBar* healthbar;
	PlaceObjects* PoManager;
	Player* pPLayer; 
	Opponent* enemy;
	PlayerBase* playerCore;
	EnemyManager* enemyManager;
	static TestLevelState  m_TestLevelState;
	bool obstacles[(World_Size / Cell_Size)*(World_Size / Cell_Size)];

};
#endif