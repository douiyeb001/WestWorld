#include <iostream>
#include <vector>

#include "TurretAI.h"
#include "Opponent.h"


vector3df turret;

TurretAI::TurretAI(EnemyManager* _pEnemyManager, vector3df newTurretPos)
{
	pEnemyManager = _pEnemyManager;
	turret = newTurretPos;
}

void TurretAI::TurretShooting(ISceneManager* pSmgr, IrrlichtDevice* pDevice) 
{
	enemySpotted = false;
	ISceneNode* enemyTarget = pSmgr->getSceneNodeFromId(17);
	float radius = 300;
	
		for (Opponent* p : opList) {
			
			SMaterial m;
			m.Lighting = false;
			pSmgr->getVideoDriver()->setMaterial(m);
			pSmgr->getVideoDriver()->setTransform(video::ETS_WORLD, core::matrix4());

			if ((p->getPosition().X >= turret.X - radius && p->getPosition().X <= turret.X + radius) &&
				(p->getPosition().Z >= turret.Z - radius && turret.Z - radius) && enemySpotted == false) {
				enemySpotted = true;

				if (enemySpotted) {
				pSmgr->getVideoDriver()->draw3DLine(turret, vector3df(p->getPosition().X, p->getPosition().Y + 5, p->getPosition().Z), SColor(255));

					ShootTimer(pDevice, p, pSmgr, turret, p->getPosition());
				}
			}
		}
	}


void TurretAI::ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent, ISceneManager* smgr, vector3df turretPosition, vector3df targetPosition) {
	if(target == NULL || target != opponent) {
		target = opponent;
		timer = pDevice->getTimer();
		start = timer->getTime();
		targeted = true;
		return;
	}

	if (timer->getTime() >= (start + 250)) {
		pEnemyManager->RemoveFromArray(opponent);
		start =  pDevice->getTimer()->getTime();
		targeted = false;
		ISceneNode* node = 0;
		node = smgr->addBillboardSceneNode(0, dimension2d<f32>(10, 10));
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("textures/fx/sprites/particlewhite.bmp"));
		node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

		ISceneNodeAnimator* anim = 0;
		const f32 speed = 0.8f;

		anim = smgr->createFlyStraightAnimator(turretPosition, vector3df(targetPosition.X, targetPosition.Y + 5, targetPosition.Z), speed);
		node->addAnimator(anim);
		anim = smgr->createDeleteAnimator(50);
		node->addAnimator(anim);
		anim->drop();
		}
	}

void TurretAI::GetList(std::vector <Opponent*> opArray){
	opList = opArray;
	
}

TurretAI::~TurretAI()
{
	opList.clear();
}
