#include <irrlicht.h>
#include <vector>
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
	ITimer* timer;
	TurretAI();
	void GetList(vector <Opponent*> opArray);
	void TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta,IrrlichtDevice* pDevice, IVideoDriver* pDriver);
	void ShootTimer(IrrlichtDevice* pDevice, Opponent* opponent);

	~TurretAI();
	std::vector <Opponent*> opList;
private:
	bool targeted = false;
};

