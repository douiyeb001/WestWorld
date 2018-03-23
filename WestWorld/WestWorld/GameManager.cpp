#include "GameStates.h"
#include "GameManager.h"

//! Default constructor
CGameManager::CGameManager()
{
	// Irrlicht device
	CreateDevice();
	// by default, we start with the introduction mode...
	m_pGameState = 0;
}

//! Default destructor
CGameManager::~CGameManager()
{
}

//! Changes the game state, calls the existing states Clear
//! function before the next states Init function
void CGameManager::ChangeState(CGameState * pState)
{
}

//! Holds a pointer to the current states, (level) Update function
//! The Update will be the game loop for the current state
void CGameManager::Update()
{
}

//! Creates the Irrlicht device and get pointers to the main subsytems
//! for later use, the Game manager is the central interface point to
//! the rendering engine
void CGameManager::CreateDevice()
{
	//Device parameters -> renderer|screen size|colour depth|full window|shadows|vsync|input device

	m_pDevice = createDevice(EDT_OPENGL, core::dimension2d<u32>(1024, 768), 32, true, false, true, this);
	if (m_pDevice == NULL)
		m_pDevice = createDevice(EDT_OPENGL, core::dimension2d<u32>(1024, 768), 32, true, false, true, this);

	m_pDriver = m_pDevice->getVideoDriver();
	m_pSceneManager = m_pDevice->getSceneManager();
	m_pGUIEnvironment = m_pDevice->getGUIEnvironment();

	Init();
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
		m_pGameState->KeyboardEvent(this);
	}

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		// Pass input down to the specific game state mouse handler
		//m_cMouse = event.MouseInput.Event;
		m_pGameState->MouseEvent(this);
	}
	return false;
}

//! Game manager genral Initialisation function. Also initialise or
//! load each of the plugable managers
void CGameManager::Init()
{
}

