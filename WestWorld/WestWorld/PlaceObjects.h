
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
//#include "MouseInput.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: video
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace video;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: scene
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace scene;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: std
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: core
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace core;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A place objects. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class PlaceObjects
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	/// <param name="smgr">  	[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	//PlaceObjects(IVideoDriver* driver, ISceneManager* smgr);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a ray. </summary>
	///
	/// <param name="camera">  	[in,out] If non-null, the camera. </param>
	/// <param name="selector">	[in,out] If non-null, the selector. </param>
	/// <param name="meta">	   	[in,out] If non-null, the meta. </param>
	/// <param name="anim">	   	[in,out] If non-null, the animation. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PlaceObjects(IVideoDriver* driver, ISceneManager* smgr, WaveManager* _waveManager, Currency* _cManager, EnemyManager* enemyManager);
	void CreateRay(scene::ICameraSceneNode *camera, scene::ITriangleSelector * selector, scene::IMetaTriangleSelector *meta, scene::ISceneNodeAnimator* anim, vector<TurretAI*> &turretlist);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Spawn turret. </summary>
	///
	/// <param name="position">	The position. </param>
	/// <param name="selector">	[in,out] If non-null, the selector. </param>
	/// <param name="meta">	   	[in,out] If non-null, the meta. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SpawnTurret(core::vector3df position, scene::ITriangleSelector *selector, scene::IMetaTriangleSelector *meta, ICameraSceneNode* camera, ISceneNodeAnimator* anim, vector<TurretAI*> &turretlist);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a collision. </summary>
	///
	/// <param name="anim">  	[in,out] If non-null, the animation. </param>
	/// <param name="camera">	[in,out] If non-null, the camera. </param>
	/// <param name="meta">  	[in,out] If non-null, the meta. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void CreateCollision(ISceneNodeAnimator *anim, scene::ICameraSceneNode *camera, scene::IMetaTriangleSelector *meta);

	void SpawnPlacementIndicator(core::vector3df position);

	void ResetPlacementIndicator();

	void MovePlacementIndicator(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates this object. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////
	

	void Update(scene::ICameraSceneNode *camera, ITriangleSelector* selector, IMetaTriangleSelector* meta, ISceneNodeAnimator* anim);
	vector<TurretAI*>  GiveList();
	/// <summary>	The intersection. </summary>
	vector3df intersection;
	/// <summary>	The hit triangle. </summary>
	triangle3df  hitTriangle;
	/// <summary>	The collided object. </summary>
	ISceneNode *collidedObject;
	/// <summary>	The ray. </summary>
	core::line3d<f32> ray;
	WaveManager* waveManager;
	///
	bool isInBuildMode;
	///
	int objectToPlace = 1;

	scene::IMeshSceneNode* placementIndicatorNode;
	std::vector <ISceneNode*> turretList;

	vector<ISceneNode*> GiveTurretArray();
	//	list<ISceneNode*> turretList;

private:
	/// <summary>	The driver. </summary>
	IVideoDriver * driver;
	EnemyManager* IEnemyManager;
	vector<TurretAI*> ITurretList;
	/// <summary>	The smgr. </summary>
	ISceneManager * smgr;
	Currency * cManager;
	
	/// <summary>	The node. </summary>
	IMeshSceneNode* node;

	bool isPlacementValid(vector3df intersection, ICameraSceneNode* player);
	///
	

	scene::IMesh* placementIndicatorMesh;
};

