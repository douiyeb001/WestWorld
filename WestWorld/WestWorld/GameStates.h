
#if !defined(AFX_GAMESTATE_H_INCLUDED_)
#define AFX_GAMESTATE_H_INCLUDED_

#include <irrlicht.h>
#include "GameManager.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CGameManager;

class CGameState
{
public:
	virtual void Init(CGameManager* pManager) = 0;
	virtual void Update(CGameManager* pManager) = 0;
	virtual void Clear(CGameManager* pManager) = 0;
	virtual void KeyboardEvent(CGameManager* pManager) = 0;
	virtual void MouseEvent(CGameManager* pManager);

	virtual ~CGameState();

protected:
	CGameState();

	void ChangeState(CGameManager* pManager, CGameState* pState);
	void FadeInOut(CGameManager* pManager);
	int m_iDebounce; // mouse
	IGUIInOutFader* m_inOutFader;
	video::SColor m_backColour;

};

#endif


