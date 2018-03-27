
#ifndef AFX_GAMEMANAGER_H_INCLUDED_
#define AFX_GAMEMANAGER_H_INCLUDED_

#include <irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CGameState;


class CGameManager : public IEventReceiver
{
public:
	void Update();
	IrrlichtDevice* getDevice();
	IVideoDriver* getDriver();
	ISceneManager* getSceneManager();
	IGUIEnvironment* getGUIEnvironment();
	ITriangleSelector* GetSelector();
	ISceneCollisionManager* GetCollManager();
	IMetaTriangleSelector* GetMeta();
	ISceneNodeAnimator* GetAnim();
	void SetAnim(ICameraSceneNode* cam);
	void SetCollision();

	char GetMouse();

	CGameManager();
	virtual ~CGameManager();
	virtual bool OnEvent(const SEvent& event);

private:
	void ChangeState(CGameState* pState);
	void CreateDevice();
	void Init();
	friend class CGameState;
	CGameState* m_pGameState;
	IrrlichtDevice* m_pDevice;
	IVideoDriver* m_pDriver;
	ISceneManager* m_pSceneManager;
	IGUIEnvironment* m_pGUIEnvironment;
	ITriangleSelector* selector;
	ISceneCollisionManager* collManager;
	IMetaTriangleSelector* meta;
	ISceneNodeAnimator* anim;

	char mouse;
};
#endif

