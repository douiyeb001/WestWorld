#ifndef TURRETAI_H
#define TURRETAI_H

#include <irrlicht.h>
#include <vector>
#include "EnemyManager.h" 
#include "Opponent.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;
class TurretAI
{
public:
	IVideoDriver * pDriver;
	EnemyManager * pEnemyManager;
	//ITimer* timer;
	IMetaTriangleSelector* pMeta;
	TurretAI(EnemyManager* _pEnemyManager, ISceneNode* newTurret, ISceneManager* smgr);
	void GetList(vector <Opponent*> opArray);
	void TurretShooting(ISceneManager* pSmgr, IrrlichtDevice* pDevice, ITriangleSelector* selector);
	void ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent, ISceneManager * smgr, vector3df turretPosition, vector3df targetPosition, ITriangleSelector* meta);
	bool enemySpotted = false;

	const float radius = 170;
	~TurretAI();
	std::vector <Opponent*> opList;
	Opponent* target;
	ISceneNode* turretNode;
private:
	int start = 0;
	bool targeted = false;
	vector3df turret;
};
#endif

