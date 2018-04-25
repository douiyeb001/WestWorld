#include <iostream>
#include <vector>

#include "TurretAI.h"
#include "Opponent.h"



TurretAI::TurretAI()
{
}

void TurretAI::TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta, IrrlichtDevice* pDevice, IVideoDriver* pDriver)
{
	bool enemySpotted = false;
	bool timerSet = false;
	ISceneNode* enemyTarget = pSmgr->getSceneNodeFromId(17);
	ISceneNode* turret = pSmgr->getSceneNodeFromName("Turret");
	float radius = 400;

	for (Opponent* p : opList) {

		SMaterial m;
		m.Lighting = false;
		pDriver->setMaterial(m);
		pDriver->setTransform(video::ETS_WORLD, core::matrix4());

		if ((p->getPosition().X >= turret->getPosition().X - radius && p->getPosition().X <= turret->getPosition().X + radius) &&
			(p->getPosition().Z >= turret->getPosition().Z - radius && turret->getPosition().Z - radius) && turret != NULL && enemySpotted == false) {
			enemySpotted = true;
			pDriver->draw3DLine(turret->getPosition(), p->getPosition(), SColor(255));
			if (enemySpotted) {
				if (!timerSet) {
					timer = new Timer(pDevice);
					timer->start();
					timerSet = true;
			
				}
				if (timer->check() >=2000) {
					//SHOOT THE ENEMY
					cout << "REE";
				}
				// check time
				
			}
		}
	}
	
}
void TurretAI::GetList(std::vector <Opponent*> opArray){
	opList = opArray;
	
}



TurretAI::~TurretAI()
{
}
