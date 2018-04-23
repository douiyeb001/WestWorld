#include "GUIBase.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="driver">	[in,out] If non-null, the driver. </param>
/// <param name="bar">   	The bar. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerHealthBar::PlayerHealthBar(IVideoDriver* driver, char const* bar) {
	hpBar = driver->getTexture(bar);
	driver->makeColorKeyTexture(hpBar, core::position2d<s32>(0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draws the given driver. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="driver">	[in,out] If non-null, the driver. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerHealthBar::Draw(IVideoDriver* driver) {
	driver->draw2DImage(hpBar, core::position2d<int>(0, driver->getScreenSize().Height - hpBar->getSize().Height), core::rect<int>(0, 0, hpBar->getSize().Width, hpBar->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="driver">	[in,out] If non-null, the driver. </param>
/// <param name="icon1"> 	The first icon. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Placeable::Placeable(IVideoDriver* driver, char const* icon1) {
	placeableIcon = driver->getTexture(icon1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draws the given driver. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="driver">	[in,out] If non-null, the driver. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Placeable::Draw(IVideoDriver* driver) {
	driver->draw2DImage(placeableIcon, core::position2d<int>(0, driver->getScreenSize().Height - placeableIcon->getSize().Height), core::rect<int>(0, 0, placeableIcon->getSize().Width, placeableIcon->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}


