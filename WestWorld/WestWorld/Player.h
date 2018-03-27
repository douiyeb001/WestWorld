#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;


class Player
{
public:
	ICameraSceneNode * getCamera();


	Player(ISceneManager* smgr);
	void CreatePlayer(ISceneManager* smgr, SKeyMap* keyMap, float movementSpeed);
	//void Update();
	void HandleMovement();
	~Player();
	void RayCreate(ISceneManager* pSmgr,IVideoDriver* pDriver, ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode*  pPlayer,IrrlichtDevice* pDevice);
	void RayUpdate(Player* RayCreate);
private:
	ICameraSceneNode* cameraNode;
	

};
#endif // !1