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
	interval = (now - beginTime);
	return interval;
}

void Timer::reset() {
	beginTime = 0;
	interval = 0;
}
