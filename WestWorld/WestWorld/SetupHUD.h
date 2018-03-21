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
	SetupHUD(IVideoDriver* driver);
	void createHUD(IVideoDriver* driver);
	void DrawAll(IVideoDriver* driver, HealthBar* hp, Placeable* icon1, Placeable* icon2, Placeable* icon3);
private:
	HealthBar* hp;
	Placeable* icon1;
	Placeable* icon2;
	Placeable* icon3;
};


#endif


