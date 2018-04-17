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


	Player(ISceneManager* smgr, IVideoDriver* driver, ISceneNodeAnimator* anim);
	void CreatePlayer(ISceneManager* smgr);
	//void Update();
	void HandleMovement();
	~Player();
	void RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode*  pPlayer, ISceneManager *smgr);
private:
	SKeyMap* pKeyMap;
	ICameraSceneNode* cameraNode;
	IVideoDriver* pDriver;
//	ISceneManager* pSmgr;

	vector3df intersection;
	triangle3df  hitTriangle;
	ISceneNode* collidedObject;

};
#endif // !1