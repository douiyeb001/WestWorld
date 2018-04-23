#include "TurretAI.h"
#include <iostream>




TurretAI::TurretAI()
{
}

void TurretAI::TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta, ISceneNodeAnimator* pAnim) {

	ISceneNode* enemyTarget = pSmgr->getSceneNodeFromName("TargetEnemy");
	ISceneNode* turret = pSmgr->getSceneNodeFromName("Turret");

	vector3df positionCheck = vector3df(20, 20, 20);

	float radius = 20;

;


	if ((enemyTarget->getPosition().X >= turret->getPosition().X - radius && enemyTarget->getPosition().X <= turret->getPosition().X +radius) && 
		(enemyTarget->getPosition().Z >= turret->getPosition().Z - radius && turret->getPosition().Z- radius ) &&turret != NULL) {
		//pMeta->removeTriangleSelector(enemyTarget->getTriangleSelector());
		//pSmgr->addToDeletionQueue(enemyTarget);
		
		
	}	



}
TurretAI::~TurretAI()
{
}
