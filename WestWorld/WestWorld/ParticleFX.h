#pragma once
#include <irrlicht.h>

#include "IDFLAGS.h"
#include "MouseInput.h"
#include "EnemySpawner.h"
#include "Currency.h"
#include "GUIBase.h"
#include "WaveManager.h"
#include  "EnemyManager.h"
#include "TurretAI.h"
#include "WaveManager.h"

using namespace irr;

using namespace video;

using namespace scene;

using namespace std;

using namespace core;


class ParticleFX
{
public:
	ParticleFX(IVideoDriver* driver, ISceneManager* smgr);
	void CreateFire(vector3df position, IVideoDriver* driver, ISceneManager* smgr);
	void CreateExplosion(vector3df position, IVideoDriver* driver, ISceneManager* smgr);

private:
	IVideoDriver * driver;
	ISceneManager * smgr;
};
