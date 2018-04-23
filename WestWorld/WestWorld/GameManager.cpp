#include "GameStates.h"
#include "GameManager.h"
#include "TestLevelState.h"

//! Default constructor
CGameManager::CGameManager()
{
	// Irrlicht device
	CreateDevice();
	// by default, we start with the introduction mode...
//	m_pGameState = TestLevelState::Instance();
	ChangeState(TestLevelState::Instance());
}

//! Default destructor
CGameManager::~CGameManager()
{
}

//! Changes the game state, calls the existing states Clear
//! function before the next states Init function
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

//! Holds a pointer to the current states, (level) Update function
//! The Update will be the game loop for the current state
void CGameManager::Update()
{
	m_pGameState->Update(this);
}

//! Creates the Irrlicht device and get pointers to the main subsytems
//! for later use, the Game manager is the central interface point to
//! the rendering engine
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

//! Returns a pointer to the Irrlicht Device subsystem
IrrlichtDevice* CGameManager::getDevice()
{
	return m_pDevice;
}

//! Returns a pointer to the Irrlicht Driver subsystem
IVideoDriver* CGameManager::getDriver()
{
	return m_pDriver;
}

//! Returns a pointer to the Irrlicht SceneManager subsystem
ISceneManager* CGameManager::getSceneManager()
{
	return m_pSceneManager;
}

//! Returns a pointer to the Irrlicht GUI subsystem
IGUIEnvironment* CGameManager::getGUIEnvironment()
{
	return m_pGUIEnvironment;
}

ITriangleSelector* CGameManager::GetSelector()
{
	return selector;
}

ISceneCollisionManager* CGameManager::GetCollManager()
{
	return collManager;
}

IMetaTriangleSelector* CGameManager::GetMeta()
{
	return meta;
}


ISceneNodeAnimator* CGameManager::GetAnim()
{
	return anim;
}

void CGameManager::SetAnim(ICameraSceneNode* cam)
{
	anim = m_pSceneManager->createCollisionResponseAnimator(meta, cam, vector3df(5,5,5), vector3df(0,-1,0));
}

void CGameManager::SetCollision()
{
	core::array<scene::ISceneNode *> nodes;
	m_pSceneManager->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

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

//! Main event handler derived from IEventHandler, this
//! will be passed down to the current states keyboard and Mouse handler.
//! The state controls its own keyboard and mouse events.
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

//! Game manager general Initialisation function. Also initialise or
//! load each of the plugable managers
void CGameManager::Init()
{
}

char CGameManager::GetMouse()
{
	return mouse;
}

