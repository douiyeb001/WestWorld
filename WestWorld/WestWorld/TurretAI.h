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
	TurretAI();
	void GetList(vector <Opponent*> opArray);
	void TurretShooting(ISceneManager* pSmgr, IrrlichtDevice* pDevice);
	void ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent);

	~TurretAI();
	std::vector <Opponent*> opList;
private:
	bool targeted = false;
};

