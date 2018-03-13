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
};