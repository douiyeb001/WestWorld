#include "TurretAI.h"
#include <iostream>
#include <vector>
#include "Opponent.h"



TurretAI::TurretAI()
{
}

void TurretAI::TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta, ISceneNodeAnimator* pAnim, IVideoDriver* pDriver)
{

	ISceneNode* enemyTarget = pSmgr->getSceneNodeFromId(17);
	ISceneNode* turret = pSmgr->getSceneNodeFromName("Turret");
	float radius = 40;

	for (Opponent* p : opList) {

		SMaterial m;
		m.Lighting = false;
		pDriver->setMaterial(m);
		pDriver->setTransform(video::ETS_WORLD, core::matrix4());

		if ((p->getPosition().X >= turret->getPosition().X - radius && p->getPosition().X <= turret->getPosition().X + radius) &&
			(p->getPosition().Z >= turret->getPosition().Z - radius && turret->getPosition().Z - radius) && turret != NULL) {
			
			pDriver->draw3DLine(turret->getPosition(), p->getPosition(), SColor(0));
		}
		
		
	}
	
}
void TurretAI::GetList(std::vector <Opponent*> opArray){
	opList = opArray;
	
}



TurretAI::~TurretAI()
{
}
