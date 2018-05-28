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
	ITimer* timer;
	IMetaTriangleSelector* pMeta;
	TurretAI(EnemyManager* _pEnemyManager, ISceneNode* newTurret);
	void GetList(vector <Opponent*> opArray);
	void TurretShooting(ISceneManager* pSmgr, IrrlichtDevice* pDevice);
	void ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent, ISceneManager * smgr, vector3df turretPosition, vector3df targetPosition);
		bool enemySpotted = false;

	~TurretAI();
	std::vector <Opponent*> opList;
	Opponent* target;
private:
	int start = 0;
	bool targeted = false;
};
#endif

