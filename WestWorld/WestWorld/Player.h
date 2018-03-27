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


	Player(ISceneManager* smgr, IVideoDriver* driver);
	void CreatePlayer(ISceneManager* smgr);
	//void Update();
	void HandleMovement();
	~Player();
	void RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode*  pPlayer);
private:
	SKeyMap* pKeyMap;
	ICameraSceneNode* cameraNode;
	IVideoDriver* pDriver;
	ISceneManager* pSmgr;

};
#endif // !1