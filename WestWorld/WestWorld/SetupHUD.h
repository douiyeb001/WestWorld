#ifndef SETUPHUD_H
#define SETUPHUD_H

#include <irrlicht.h>

#include "GUIbase.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;


class SetupHUD {
public:
	SetupHUD();
	void createHUD(IVideoDriver* driver);
private:
	HealthBar* hp;
	Placeable* icon1;
	Placeable* icon2;
	Placeable* icon3;
};


#endif


