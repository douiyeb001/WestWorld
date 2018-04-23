#include "TestLevelState.h"


/// <summary>	State of the test level state m test level. </summary>
TestLevelState TestLevelState::m_TestLevelState;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

TestLevelState::TestLevelState(){

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

TestLevelState::~TestLevelState(){

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the instance. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else a pointer to a TestLevelState. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

TestLevelState* TestLevelState::Instance(){
	return(&m_TestLevelState);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Initializes this object. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void TestLevelState::Init(CGameManager* pManager) {
	//m_titlePic = pManager->getDriver()->getTexture("media/fire.jpg");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads the scene. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	pManager->getSceneManager()->loadScene("scene/T_Placing.irr");
	/// <summary>	Player </summary>
	pPLayer = new Player(pManager->getSceneManager(),pManager->getDriver(), pManager->GetAnim());
	/// <summary>	Camera. </summary>
	cameraNode = pPLayer->getCamera();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	 </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="cameraNode">	The first parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	pManager->SetAnim(cameraNode);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Add animator. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	cameraNode->addAnimator(pManager->GetAnim());

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Collision. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	pManager->SetCollision();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Animation ... </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	pManager->GetAnim()->drop();
	/// <summary>	Add the healthbar. </summary>
	healthbar = new PlayerHealthBar(pManager->getDriver(), "media/UI/HealthBarDefinitelyNotStolen.png");
	/// <summary>	Place objects. </summary>
	PoManager = new PlaceObjects(pManager->getDriver(), pManager->getSceneManager());
	
	//bool obstacles[1000];//[(World_Size / Cell_Size)*(World_Size / Cell_Size)];
	std::fill(std::begin(obstacles), std::end(obstacles), false);

	/// <summary>	The children. </summary>
	irr::core::list<scene::ISceneNode*> children = pManager->getSceneManager()->getRootSceneNode()->getChildren();
	/// <summary>	The iterator. </summary>
	core::list<scene::ISceneNode*>::Iterator it = children.begin();
	for (; it != children.end(); ++it)
	{
		if ((*it)->getID()) {
			s32 id = (*it)->getID();
			if (id == 10)

				for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++) {
					for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++) {
						// Do something with the node here.
						irr::core::aabbox3df box = irr::core::aabbox3df(x *Cell_Size - Cell_Size / 2, 0, z *Cell_Size - Cell_Size / 2, (x + 1)*Cell_Size + Cell_Size / 2, 0, (z + 1)*Cell_Size + Cell_Size / 2);

						if ((*it)->getTransformedBoundingBox().intersectsWithBox(box))
						{
							obstacles[((x)+World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z)+World_Size / (2 * Cell_Size))] = true;
						}
					}
				}
		}
	}
	/// <summary>	Playerbase. </summary>
	playerCore = new PlayerBase(pManager->getSceneManager()->getSceneNodeFromName("house"), pManager->getSceneManager());
	/// <summary>	Enemy. </summary>
	enemy = new Opponent(pManager->getSceneManager()->getSceneNodeFromId(1), pManager->getSceneManager()->getSceneNodeFromName("Ground"),playerCore, obstacles);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Clears this object to its blank/initial state. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void TestLevelState::Clear(CGameManager* pManager) {

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the given pManager. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void TestLevelState::Update(CGameManager* pManager) {
	pManager->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
	pManager->getSceneManager()->drawAll();

	enemy->Update();
	
	healthbar->Draw(pManager->getDriver());

	pManager->getGUIEnvironment()->drawAll();
	pManager->getDriver()->endScene();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Keyboard event. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void TestLevelState::KeyboardEvent(CGameManager* pManager) {

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Mouse event. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pManager">	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void TestLevelState::MouseEvent(CGameManager* pManager) {
	// Remember the mouse statess
	//bool isDown = false;

	if (pManager->GetMouse() == EMIE_RMOUSE_PRESSED_DOWN)
	{
	//	isDown = true;
		// spawn turret function insert here
	//	int idTest = PoManager->collidedObject->getID();
		//if (PoManager->collidedObject->getID() == IDFlag::spawnGround)
		//{
		PoManager->CreateRay(cameraNode, pManager->GetSelector(), pManager->GetMeta(), pManager->GetAnim());		
	}

	if (pManager->GetMouse() == EMIE_LMOUSE_PRESSED_DOWN) {
		pPLayer->RayCreate(pManager->GetSelector(), pManager->GetMeta(),cameraNode, pManager->getSceneManager());
		
	}
	if (pManager->GetMouse() == EMIE_RMOUSE_LEFT_UP)
	{
		//isDown = false;
	}
}