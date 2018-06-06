#include <iostream>
#include <vector>

#include "TurretAI.h"
#include "Opponent.h"

line3df ray;
ICameraSceneNode* cam;

TurretAI::TurretAI(EnemyManager* _pEnemyManager, vector3df newTurretPos, ISceneManager* smgr)
{
	pEnemyManager = _pEnemyManager;
	turret = newTurretPos;
	cam = smgr->addCameraSceneNode(0, vector3df(0, 0, 0),vector3df(0,0,0),0,false);
	vector3df turretRayPos = vector3df(turret.X, turret.Y + 40, turret.Z);
	cam->setPosition(turretRayPos);
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
				pSmgr->getVideoDriver()->draw3DLine(turret, vector3df(p->getPosition().X, p->getPosition().Y + 5, p->getPosition().Z), SColor(255));

					ShootTimer(pDevice, p, pSmgr, turret, p->getPosition(), selector);
				}
			}
		}
	}

void TurretAI::ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent, ISceneManager* smgr, vector3df turretPosition, vector3df targetPosition, ITriangleSelector* selector) {

	if(target == NULL || target != opponent) {
		target = opponent;
		timer = pDevice->getTimer();
		start = timer->getTime();
		targeted = true;
		return;
	}


		opponent->target = NULL;
		opponent->isExploding = true;
		//pEnemyManager->RemoveFromArray(opponent);

	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	vector3df intersection;
	triangle3df hitTriangle;

	ray.start = turretPosition;
	cam->setTarget(opponent->getPosition());
//	ray.end = opponent->getPosition();
	ray.end = cam->getTarget();
	vector3df end = vector3df(ray.end.X, ray.end.Y + 5, ray.end.Z);
	ray.end = end;

	ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle,
			0, 0);

//	end.normalize();
//	end = startPos + (end);
	line3d<f32> line(ray.start, end);
	ISceneNode* test;

	if (collMan->getCollisionPoint(line, selector, end, hitTriangle, test)) {
		vector3df out = hitTriangle.getNormal();
		//OnShoot(end, smgr);
		//out.setLength(0.03f);
		line.end = end;
	}

	smgr->getVideoDriver()->draw3DLine(ray.start, line.end, SColor(255));

	line3d<f32>bbLine (ray.start, line.end);

	ISceneNode* bbNode = collMan->getSceneNodeFromRayBB(bbLine, 17);
	if ( bbNode) {
		if ( bbNode->getID() == 17) {
			printf("coolio");
		}
	}

	/*if (timer->getTime() >= (start + 1000)) {
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
		}*/
	}

void TurretAI::GetList(std::vector <Opponent*> opArray){
	opList = opArray;
	
}

TurretAI::~TurretAI()
{
	opList.clear();
}
