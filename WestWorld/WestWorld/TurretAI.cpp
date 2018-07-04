#include <iostream>
#include <vector>

#include "TurretAI.h"
#include "Opponent.h"
#include "Timer.h"

line3df ray;
ICameraSceneNode* cam;
Timer* timer;

TurretAI::TurretAI(EnemyManager* _pEnemyManager, ISceneNode* newTurret, ISceneManager* smgr, irrklang::ISoundEngine* SoundEngine)
{
	pEnemyManager = _pEnemyManager;
	turret = newTurret->getPosition();
	turretNode = newTurret;
	cam = smgr->addCameraSceneNode(0, vector3df(0, 0, 0),vector3df(0,0,0),0,false);
	vector3df turretRayPos = vector3df(turret.X, turret.Y + 40, turret.Z);
	cam->setPosition(turretRayPos);
	iSoundEngine = SoundEngine;
}

void TurretAI::TurretShooting(ISceneManager* pSmgr, IrrlichtDevice* pDevice, ITriangleSelector* selector) 
{
	enemySpotted = false;
	ISceneNode* enemyTarget = pSmgr->getSceneNodeFromId(17);
	
		for (Opponent* p : opList) {
			
			SMaterial m;
			m.Lighting = false;
			pSmgr->getVideoDriver()->setMaterial(m);
			pSmgr->getVideoDriver()->setTransform(video::ETS_WORLD, core::matrix4());

			if ((p->getPosition().X >= turret.X - radius && p->getPosition().X <= turret.X + radius) &&
				(p->getPosition().Z >= turret.Z - radius && p->getPosition().Z <= turret.Z + radius) && enemySpotted == false) {
				enemySpotted = true;

				//if (selectedSceneNode != NULL && selectedSceneNode->getID() != 10) {
				//	// alleen maar als not collide mit wall
				//	enemySpotted = true;
				//}


				if (enemySpotted) {
					vector3df dir =  vector3df(p->getPosition().X, p->getPosition().Y + 5, p->getPosition().Z)- turretNode->getPosition() ;
					turretNode->setRotation(dir.getHorizontalAngle());
				pSmgr->getVideoDriver()->draw3DLine(turret, vector3df(p->getPosition().X, p->getPosition().Y + 5, p->getPosition().Z), SColor(255));

					ShootTimer(pDevice, p, pSmgr, turret, p->getPosition(), selector);
				}
			}
		}
	}

void TurretAI::ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent, ISceneManager* smgr, vector3df turretPosition, vector3df targetPosition, ITriangleSelector* selector) {
	if (timer == nullptr)
		timer = new Timer(pDevice);

	if(target == NULL || target != opponent) {
		timer->set(1200);
		target = opponent;
		targeted = true;
		shot = false;
		return;
	}


		

	if (timer->alarm() && !shot) {
		start =  pDevice->getTimer()->getTime();
		iSoundEngine->play2D("media/Sound/CannonWav.wav", false);
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
		opponent->target = NULL;
		opponent->isExploding = true;
		//pEnemyManager->RemoveFromArray(opponent);
		shot = true;
		}
	}

void TurretAI::GetList(std::vector <Opponent*> opArray){
	opList = opArray;
	
}

TurretAI::~TurretAI()
{
	opList.clear();
}
