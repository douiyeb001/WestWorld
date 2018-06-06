#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>

using namespace irr;


#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	MouseInput.h
//
// summary:	store the latest state of the mouse updating them as we receive events.
////////////////////////////////////////////////////////////////////////////////////////////////////

class MouseInput : public IEventReceiver
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	create a struct to record info on the mouse state. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SMouseState
	{
		core::position2di Position;
		bool IsRightButtonDown;
		SMouseState() : IsRightButtonDown(false) { }
	} MouseState;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Event check what mouse input is being used - From the irrlicht Tutorial. </summary>
	///
	/// <param name="event">	The event. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool OnEvent(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			switch (event.MouseInput.Event)
			{
			case EMIE_RMOUSE_PRESSED_DOWN:
				MouseState.IsRightButtonDown = true;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				MouseState.IsRightButtonDown = false;
				break;

			default:
				break;
			}
		}
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets mouse state. </summary>
	///
	/// <returns>	The mouse state. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}
};
#endif // ! 