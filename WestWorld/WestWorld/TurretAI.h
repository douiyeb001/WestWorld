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
	TurretAI();
	void GetList(vector <Opponent*> opArray);
	void TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta,ISceneNodeAnimator* pAnim, IVideoDriver* pDriver);

	~TurretAI();
	std::vector <Opponent*> opList;

};

