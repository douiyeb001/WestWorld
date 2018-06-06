#include "GameStates.h"
#include "GameManager.h"
#include "TestLevelState.h"
#include  "MenuState.h"
#include <chrono>
#include <thread>

//! Default constructor
CGameManager::CGameManager(){
	// Irrlicht device
	CreateDevice();
	// by default, we start with the introduction mode...
//	gameState = TestLevelState::Instance();
	ChangeState(MenuState::Instance());
}

//! Default destructor
CGameManager::~CGameManager(){
}

//! Cleans up the existing state,
//! switches state and inititializes the new state
void CGameManager::ChangeState(CGameState * pState){
	if (gameState)
		gameState->Clear(this);
	if (pState != gameState){
		gameState = pState;
		gameState->Init(this);
	}	
}

void CGameManager::ReinitializeState(CGameState * pState){
	gameState->Clear(this);
	gameState->Init(this);
}

//! Holds a pointer to the current states, (level) Update function
//! The Update will be the game loop for the current state
void CGameManager::Update(){
	gameState->Update(this);
}

//! Creates the Irrlicht device and get pointers to the main subsytems
//! for later use, the Game manager is the central interface point to
//! the rendering engine
void CGameManager::CreateDevice(){
	//Device parameters -> renderer|screen size|colour depth|full window|shadows|vsync|input device
	device = createDevice(EDT_DIRECT3D9, core::dimension2d<u32>(1280, 720), 32, false, false, false, this);
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	guiEnvironment = device->getGUIEnvironment();
	selector = nullptr;
	meta = sceneManager->createMetaTriangleSelector();
	collisionManager = sceneManager->getSceneCollisionManager();
}

//! Returns a pointer to the Irrlicht Device subsystem
IrrlichtDevice* CGameManager::getDevice(){
	return device;
}

//! Returns a pointer to the Irrlicht Driver subsystem
IVideoDriver* CGameManager::getDriver(){
	return driver;
}

//! Returns a pointer to the Irrlicht SceneManager subsystem
ISceneManager* CGameManager::getSceneManager(){
	return sceneManager;
}

//! Returns a pointer to the Irrlicht GUI subsystem
IGUIEnvironment* CGameManager::getGUIEnvironment(){
	return guiEnvironment;
}

ITriangleSelector* CGameManager::GetSelector()
{
	return selector;
}

ISceneCollisionManager* CGameManager::GetCollManager()
{
	return collisionManager;
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
anim = sceneManager->createCollisionResponseAnimator(meta, cam, vector3df(15,15,15), vector3df(0,-1,0));
}

void CGameManager::SetCollision()
{
	core::array<scene::ISceneNode *> nodes;
	sceneManager->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

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
			selector = sceneManager->createTriangleSelectorFromBoundingBox(node);
			break;

		case scene::ESNT_MESH:
		case scene::ESNT_SPHERE: // Derived from IMeshSceneNode
			selector = sceneManager->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;

		case scene::ESNT_TERRAIN:
			selector = sceneManager->createTerrainTriangleSelector((scene::ITerrainSceneNode*)node);
			break;

		case scene::ESNT_OCTREE:
			selector = sceneManager->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
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
	if (!driver)
		return false;

	//Recognize key when key is  released
	if (event.EventType == EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
	{
		keyboard = event.KeyInput.Key;
		gameState->KeyboardEvent(this);
	//	m_bKeys[event.KeyInput.Key] = event.KeyInput.PressedDown;

		// Pass input down to the specific game state keyboard handler
	//	gameState->KeyboardEvent(this);
	}

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		// Pass input down to the specific game state mouse handler
		mouse = event.MouseInput.Event;
		gameState->MouseEvent(this);
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

char CGameManager::GetKeyboard()
{
	return keyboard;
}
