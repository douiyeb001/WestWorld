#include "timer.h"


Timer::Timer(IrrlichtDevice* device)
{
	irrTimer = device->getTimer();
	irrTimer->getTime();
}

Timer::~Timer(void)
{
}

void Timer::set(int timeout) {
	beginTime = irrTimer->getTime();
	interval = timeout;
}

void Timer::start() {
	beginTime = irrTimer->getTime();
	previousTime = beginTime;
	interval = 0;
}

bool Timer::alarm() {
	int now = irrTimer->getTime();
	if ((now - beginTime) >= interval) {
		return true;
	}
	else {
		return false;
	}
}

int Timer::stop() {
	int now = irrTimer->getTime();
	interval = (now - beginTime);
	return interval;
}
int Timer::check() {
	int now = irrTimer->getTime();
	int timeLeft = (interval - (now - beginTime));
	return timeLeft;
}

void Timer::reset() {
	beginTime = 0;
	interval = 0;
}

int Timer::deltaTime() {
	int now = irrTimer->getTime();
	int deltaTime = now - previousTime;
	previousTime = now;
	return deltaTime;
}
