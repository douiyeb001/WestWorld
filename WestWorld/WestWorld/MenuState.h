#pragma once
#ifndef  MenuState_H
#define  MenuState_H

#include "GameStates.h"
#include "Sprite.h"

using namespace irr;
using namespace video;
using namespace core;

enum menuStateID {
	START = 0,
	CONTROLS = 1,
	QUIT = 2
};

class MenuState : public CGameState{
public:
	virtual void Init(CGameManager* pManager);
	virtual void Clear(CGameManager* pManager);
	virtual void Update(CGameManager * pManager);
	virtual void KeyboardEvent(CGameManager* pManager);
	virtual void MouseEvent(CGameManager* pManager);

	static MenuState* Instance();
	int currentMenuId = 0;
	virtual ~MenuState();

protected:
	MenuState();
	Sprite* backgroundSprite;
	Sprite* revolverSprite;
	bool onControlScreen = false;
	Sprite* controlSchemeSprite;
	ICameraSceneNode* m_pCamera;
	ISceneNode* m_pNode;
	position2d<s32> m_MousePos;
	void DisplayMouse(CGameManager* pManager);
	bool m_bMouseMode;
private:
	static MenuState m_MenuState; // singleton...
									// local game variables
	void MouseClicked(CGameManager* pManager);
	ISceneManager* ismgr;
};



#endif




