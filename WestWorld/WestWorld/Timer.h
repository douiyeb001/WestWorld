#ifndef TTIMER_H
#define TTIMER_H

#include <irrlicht.h>


using namespace irr;
using namespace core;

class Timer
{
public:
	Timer(IrrlichtDevice* device);
	~Timer(void);
	void set(int timeout);
	void start();
	bool alarm();
	int stop();
	int check();
	void reset();
	int deltaTime();
private:
	int beginTime;
	int interval;
	ITimer* irrTimer;
	int previousTime;
};

#endif