#include <irrlicht.h>

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
	void TurretShooting(ISceneManager* pSmgr, IMetaTriangleSelector* pMeta,ISceneNodeAnimator* pAnim);
	core::line3d<f32> ray;

	~TurretAI();
};

