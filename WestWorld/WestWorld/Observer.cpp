#include "Observer.h"
#include "stdafx.h"
#include <string>
#include "MenuState.h"
#include "GUIBase.h"



Observer::Observer()
{

}

void Observer::SwitchState(currentEvent e) {
	now = e;
	switch (currentEvent(now)) {
	case WALK:
		tutText = "Press WASD to move around";
		break;
	case SHOOT:
		tutText = "Press LMB to shoot your gun";
		break;
	case KILLENEMY:
		tutText = "Shoot at an enemy to kill it";
		// spawned enemy to position
		break;
	case SPAWNOBSTACLE:
		tutText = "Press 1 to select a barricade and press RMB to place it";
		break;
	case SPAWNTURRET:
		tutText = "Press 2 to select a turret and press RMB to place it";
		break;
	case ENDTUTORIAL:
		tutText = "You have finished the tutorial, the game will begin shortly";
		// end tutorial text..
		break;
	}
}

void Observer::Update() {
	

}




Observer::~Observer()
{
}

Listener::Listener() {  }

void Listener::Attach(Observer* observer) {
	obs = observer;
}

void Listener::Detach(Observer* observer) {
	obs = nullptr;
}

void Listener::Notify(Listener* listener, currentEvent e) {
	if (!listener->obs)return;

	obs->SwitchState(e);
	listener->Detach(listener->obs);
}

Listener::~Listener() {  }
