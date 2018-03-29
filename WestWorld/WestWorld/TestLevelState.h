#ifndef TestLevelState_H
#define TestLevelState_H

#include "GamePlayState.h"
#include "GUIBase.h"
#include "PlaceObjects.h" 
#include "Player.h"

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
	static TestLevelState  m_TestLevelState;
};
#endif