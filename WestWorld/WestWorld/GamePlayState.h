#if !defined(AFX_CGAMEPLAYSTATE_H_INCLUDED_)
#define AFX_CGAMEPLAYSTATE_H_INCLUDED_

#include "GameStates.h"

class CGamePlayState : public CGameState
{
public:
	virtual void Init(CGameManager* pManager);
	virtual void Clear(CGameManager* pManager);
	virtual void Update(CGameManager * pManager);
	virtual void KeyboardEvent(CGameManager* pManager);
	virtual void MouseEvent(CGameManager* pManager);

	static CGamePlayState* Instance();
	virtual ~CGamePlayState();

	int SelMdl;
protected:
	CGamePlayState();
	void DisplayFPS(CGameManager* pManager);
	void LoadMap(CGameManager* pManager, const c8 *map);
	IGUIStaticText* m_statusText;
	wchar_t m_tmp[255];

	scene::ITriangleSelector* m_Selector;

private:
	static CGamePlayState m_PlayState; // singleton...

};
#endif

