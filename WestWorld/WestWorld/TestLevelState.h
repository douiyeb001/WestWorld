#ifndef TestLevelState_H
#define TestLevelState_H

#include "GamePlayState.h"

class TestLevelState : public CGamePlayState {

public:
	virtual void Init(CGameManager* pManager);
	virtual void Clear(CGameManager* pManager);
	virtual void Update(CGameManager* pManager);
	virtual void KeyboardEvent(CGameManager* pManager);

	static TestLevelState* Instance();
	virtual ~TestLevelState();

protected:
	TestLevelState();

private:
	static TestLevelState  m_TestLevelState;
};
#endif