#include <iostream>
#include <vector>

#include "TurretAI.h"
#include "Opponent.h"



TurretAI::TurretAI(EnemyManager* _pEnemyManager)
{
	pEnemyManager = _pEnemyManager;
}

void TurretAI::TurretShooting(ISceneManager* pSmgr, IrrlichtDevice* pDevice)
{

	enemySpotted = false;
	ISceneNode* enemyTarget = pSmgr->getSceneNodeFromId(17);
	ISceneNode* turret = pSmgr->getSceneNodeFromName("Turret");
	float radius = 500;

	for (Opponent* p : opList) {

		SMaterial m;
		m.Lighting = false;
		pSmgr->getVideoDriver()->setMaterial(m);
		pSmgr->getVideoDriver()->setTransform(video::ETS_WORLD, core::matrix4());

		if ((p->getPosition().X >= turret->getPosition().X - radius && p->getPosition().X <= turret->getPosition().X + radius) &&
			(p->getPosition().Z >= turret->getPosition().Z - radius && turret->getPosition().Z - radius) && enemySpotted == false) {
			enemySpotted = true;

			pSmgr->getVideoDriver()->draw3DLine(turret->getPosition(), p->getPosition(), SColor(255));
			if (enemySpotted) {
				ShootTimer(pDevice, p);
			}
		}
		else {
			enemySpotted = false;
		}
	}
}

void TurretAI::ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent) {

	if (!targeted) {
		timer = pDevice->getTimer();
		start = timer->getTime();
		targeted = true;
	}
//	timer->tick();
	if (timer->getTime() >= (start + 2000)) {
		pEnemyManager->RemoveFromArray(opponent);
		//enemySpotted = false;
		targeted = false;
		//start =  pDevice->getTimer()->getTime();
	}

	}



void TurretAI::GetList(std::vector <Opponent*> opArray){
	opList = opArray;
	
}



TurretAI::~TurretAI()
{
}
