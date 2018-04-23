#include "Game.h"
#include "GamePlayState.h"
//#include "TestLevelState.h"
#include "GameStates.h"

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif


//! Default constructor
CGameState::CGameState()
{

}

//! Default destructor
CGameState::~CGameState()
{

}

//! Overridden by subclass.
//! Change state, overridden by subclasses
void CGameState::ChangeState(CGameManager * pManager, CGameState * pState)
{
	pManager->ChangeState(pState);
}

//! Implemented by subclass
//! Keyboard event for state, main keyboard events
//! passed down by Game manager. 
void CGameState::KeyboardEvent(CGameManager* pManager)
{

}

//! Implemented by subclass
//! Mouse event for state, main mouse events
//! passed down by Game manager. 
void CGameState::MouseEvent(CGameManager* pManager)
{

}

//! Implemented by subclass
//! Initialisation, loads data required for state. 
void CGameState::Init(CGameManager * pManager)
{

}

//! Implemented by subclass
//! Update, moves and renders screen.
void CGameState::Update(CGameManager * pManager)
{

}

//! Implemented by subclass
//! Clear, tidy up
void CGameState::Clear(CGameManager* pManager)
{

}

//! Fades the screen In/Out
void CGameState::FadeInOut(CGameManager* pManager)
{
	// fade in and disable cursor
	pManager->getDevice()->getCursorControl()->setVisible(false);
	m_inOutFader = pManager->getDevice()->getGUIEnvironment()->addInOutFader();
	m_backColour.set(255,0,0,0); //255 90 90 156
	m_inOutFader->setColor(m_backColour);
	m_inOutFader->fadeIn(1500);
}
