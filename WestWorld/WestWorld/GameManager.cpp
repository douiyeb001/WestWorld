#include "GameStates.h"
#include "GameManager.h"
#include "TestLevelState.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CGameManager::CGameManager()
{
	// Irrlicht device
	CreateDevice();
	// by default, we start with the introduction mode...
//	m_pGameState = TestLevelState::Instance();
	ChangeState(TestLevelState::Instance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

CGameManager::~CGameManager()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Changes the game state, calls the existing states Clear function before the next states Init function </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pState">	[in,out] If non-null, the state. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGameManager::ChangeState(CGameState * pState)
{
	if (m_pGameState)
		m_pGameState->Clear(this);
	if (pState != m_pGameState)
	{
		m_pGameState = pState;
		m_pGameState->Init(this);
	}
}

//! 

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Holds a pointer to the current states, (level) Update function.
/// 			The Update will be the game loop for the current state </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGameManager::Update()
{
	m_pGameState->Update(this);
}

//! 

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Creates the Irrlicht device and get pointers to the main subsytems for later use, 
/// 			the Game manager is the central interface point to the rendering engine </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGameManager::CreateDevice()
{
	//Device parameters -> renderer|screen size|colour depth|full window|shadows|vsync|input device

	m_pDevice = createDevice(EDT_DIRECT3D9, core::dimension2d<u32>(1280, 720), 32, false, false, false, this);
	if (m_pDevice == NULL)
		m_pDevice = createDevice(EDT_DIRECT3D9, core::dimension2d<u32>(1280, 720), 32, false, false, false, this);
	m_pDriver = m_pDevice->getVideoDriver();
	m_pSceneManager = m_pDevice->getSceneManager();
	m_pGUIEnvironment = m_pDevice->getGUIEnvironment();
	selector = 0;
	meta = m_pSceneManager->createMetaTriangleSelector();
	collManager = m_pSceneManager->getSceneCollisionManager();

	
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	 Returns a pointer to the Irrlicht Device subsystem </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the device. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

IrrlichtDevice* CGameManager::getDevice()
{
	return m_pDevice;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Returns a pointer to the Irrlicht Driver subsystem </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the driver. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

IVideoDriver* CGameManager::getDriver()
{
	return m_pDriver;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	 Returns a pointer to the Irrlicht SceneManager subsystem </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the scene manager. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

ISceneManager* CGameManager::getSceneManager()
{
	return m_pSceneManager;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Returns a pointer to the Irrlicht GUI subsystem </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the graphical user interface environment. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

IGUIEnvironment* CGameManager::getGUIEnvironment()
{
	return m_pGUIEnvironment;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the selector. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the selector. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

ITriangleSelector* CGameManager::GetSelector()
{
	return selector;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets collection manager. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the collection manager. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

ISceneCollisionManager* CGameManager::GetCollManager()
{
	return collManager;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the meta. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the meta. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

IMetaTriangleSelector* CGameManager::GetMeta()
{
	return meta;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the animation. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the animation. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

ISceneNodeAnimator* CGameManager::GetAnim()
{
	return anim;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets an animation. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="cam">	[in,out] If non-null, the camera. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGameManager::SetAnim(ICameraSceneNode* cam)
{
	/// <summary>	. </summary>
	anim = m_pSceneManager->createCollisionResponseAnimator(meta, cam, vector3df(5,5,5), vector3df(0,-1,0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets the collision. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGameManager::SetCollision()
{
	/// <summary>	The nodes. </summary>
	core::array<scene::ISceneNode *> nodes;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Find all the nodes. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="scene::ESNT_ANY, nodes">	The first parameter. </param>
	/// <param name="nodes">	The second parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pSceneManager->getSceneNodesFromType(scene::ESNT_ANY, nodes); 

	for (u32 i = 0; i < nodes.size(); ++i)
	{
		scene::ISceneNode * node = nodes[i];


		switch (node->getType())
		{
		case scene::ESNT_CUBE:
		case scene::ESNT_ANIMATED_MESH:
			// Because the selector won't animate with the mesh,
			// and is only being used for camera collision, we'll just use an approximate
			// bounding box instead of ((scene::IAnimatedMeshSceneNode*)node)->getMesh(0)
			selector = m_pSceneManager->createTriangleSelectorFromBoundingBox(node);
			break;

		case scene::ESNT_MESH:
		case scene::ESNT_SPHERE: // Derived from IMeshSceneNode
			selector = m_pSceneManager->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;

		case scene::ESNT_TERRAIN:
			selector = m_pSceneManager->createTerrainTriangleSelector((scene::ITerrainSceneNode*)node);
			break;

		case scene::ESNT_OCTREE:
			selector = m_pSceneManager->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;

		default:
			// Don't create a selector for this node type
			break;
		}

		if (selector)
		{
			// Add it to the meta selector, which will take a reference to it
			meta->addTriangleSelector(selector);
			// And drop my reference to it, so that the meta selector owns it.
			selector->drop();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Main event handler derived from IEventHandler, this will be passed down to the current states keyboard and Mouse handler. 
/// 			The state controls its own keyboard and mouse events. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="event">	The event. </param>
///
/// <returns>	True if it succeeds, false if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool CGameManager::OnEvent(const SEvent& event)
{
	if (!m_pDriver)
		return false;

	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
	//	m_bKeys[event.KeyInput.Key] = event.KeyInput.PressedDown;

		// Pass input down to the specific game state keyboard handler
	//	m_pGameState->KeyboardEvent(this);
	}

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		// Pass input down to the specific game state mouse handler
		mouse = event.MouseInput.Event;
		m_pGameState->MouseEvent(this);
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Game manager general Initialisation function. Also initialise or load each of the plugable managers </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void CGameManager::Init()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the mouse. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	The mouse. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

char CGameManager::GetMouse()
{
	return mouse;
}

