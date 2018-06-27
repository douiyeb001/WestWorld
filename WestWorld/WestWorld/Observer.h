#pragma once
#include <memory>
#include <vector>
#include <list>
#include <algorithm>

enum currentEvent { WALK, SHOOT, KILLENEMY, SPAWNOBSTACLE, SPAWNTURRET, ENDTUTORIAL };

class Observer
{
public:
	Observer();

	void SwitchState(currentEvent e);
	currentEvent now;
	void Update();

	~Observer();
};

class Listener {
public:
	Listener();

	Observer* obs;

	void Attach(Observer* observer);
	void Detach(Observer* observer);
	void Notify(Listener* listener, currentEvent e);

	~Listener();
};

