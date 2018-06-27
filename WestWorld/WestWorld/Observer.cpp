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
		printf("");
		break;
	case SHOOT:
		printf("");
		break;
	case KILLENEMY:
		printf("");
		// spawned enemy to position
		break;
	case SPAWNOBSTACLE:
		printf("");
		break;
	case SPAWNTURRET:
		printf("");
		break;
	case ENDTUTORIAL:
		printf("");
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
