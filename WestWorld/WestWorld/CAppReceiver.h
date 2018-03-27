#include <irrlicht.h>
#include "driverChoice.h"


using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif
class CAppReceiver : public IEventReceiver
{
private:
	bool KeyDown[KEY_KEY_CODES_COUNT];

public:
	CAppReceiver()
	{
		for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
		{
			KeyDown[i] = false;
		}
	}

	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	//Mouse
	virtual bool OnEventMouse(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch (event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}
		return false;
	}
	//keyboard
	virtual bool OnEvent(const SEvent& event)
	{
		switch (event.EventType)
		{
		case EET_KEY_INPUT_EVENT:
		{
			KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			break;
		}
		default:
			break;
		}
		return false;
	}
	virtual bool isKeyDown(EKEY_CODE keyCode) const
	{
		return KeyDown[keyCode];
	}
	virtual bool isKeyUp(EKEY_CODE keyCode) const
	{
		return !KeyDown[keyCode];
	}


	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}

};