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
	Player(ISceneManager* smgr);
	void CreatePlayer(ISceneManager* smgr, SKeyMap* keyMap, float movementSpeed);
	//void Update();
	void HandleMovement();
	~Player();
};
#endif // !1