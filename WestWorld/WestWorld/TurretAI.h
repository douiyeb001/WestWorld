#include <irrlicht.h>
#include <vector>
#include "Opponent.h"
#include "Timer.h"

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
	Timer* timer;
	TurretAI();
	void GetList(vector <Opponent*> opArray);
	void TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta,IrrlichtDevice* pDevice, IVideoDriver* pDriver);

	~TurretAI();
	std::vector <Opponent*> opList;

};

