 #include "GUIBase.h"
#include <stdio.h> 

PlayerHealthBar::PlayerHealthBar(IVideoDriver* driver, char const* bar) {
	hpBar = driver->getTexture(bar);
	driver->makeColorKeyTexture(hpBar, core::position2d<s32>(0, 0));
}

void PlayerHealthBar::Draw(IVideoDriver* driver) {
	driver->draw2DImage(hpBar, core::position2d<int>(0, driver->getScreenSize().Height - hpBar->getSize().Height), core::rect<int>(0, 0, hpBar->getSize().Width, hpBar->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}

Placeable::Placeable(IVideoDriver* driver, char const* icon1) {
	placeableIcon = driver->getTexture(icon1);
}

void Placeable::Draw(IVideoDriver* driver) {
	driver->draw2DImage(placeableIcon, core::position2d<int>(0, driver->getScreenSize().Height - placeableIcon->getSize().Height), core::rect<int>(0, 0, placeableIcon->getSize().Width, placeableIcon->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}

Reticle::Reticle(IVideoDriver* driver, char const* reticle) {
	reticleSprite = driver->getTexture(reticle);
}
CurrencyUI::CurrencyUI(IVideoDriver* driver, char const* pDollar, char const* pInfinity) {
	//font = device->getGUIEnvironment()->getFont("medi.bmp");
	//pScore = (const wchar_t*)cManager->playerCurrency;
	pDollarTexture = driver->getTexture(pDollar);
	pInfinityTexture = driver->getTexture(pInfinity);

}
GameOverScreen::GameOverScreen(IVideoDriver* driver, char const* deadLogo){
	GameOverSprite = driver->getTexture(deadLogo);


}


void Reticle::Draw(IVideoDriver* driver) {
	driver->draw2DImage(reticleSprite, core::position2d<int>((driver->getScreenSize().Width - reticleSprite->getSize().Width )/2, (driver->getScreenSize().Height - reticleSprite->getSize().Height)/2), core::rect<int>(0, 0, reticleSprite->getSize().Width, reticleSprite->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw shooting reticle
}
void CurrencyUI::Draw(IGUIEnvironment* gui, IVideoDriver* driver) {
	
	//pStaticText = gui->addStaticText(pText, rect<s32>(20, 30, 220, 50), false);
//	pText = (const wchar_t)cManager->playerCurrency;
		//swprintf_s(pText, L"%d", cManager->playerCurrency);
	//pScoreText = gui->addStaticText(pText, rect<s32>(70, 30, 270, 50), false);
	
	
	//pScoreText = gui->addStaticText(pScore, rect<s32>(70, 30, 270, 50), false);
	//if (font)
	//{
	//	font->draw((L"%d", (stringc)cManager->playerCurrency),
	//		core::rect<s32>(70, 30, 270, 50),
	//		video::SColor(255, 0, 0, 0));
	//}
	driver->draw2DImage(pDollarTexture, 
		core::position2d<int>(20, 20), 
		core::rect<int>(0, 0, pDollarTexture->getSize().Width, pDollarTexture->getSize().Height), 
		0, 
		video::SColor(255, 255, 255, 255), true); //Draw bar

	driver->draw2DImage(pInfinityTexture,
		core::position2d<int>(100, 0),
		core::rect<int>(0, 0, pInfinityTexture->getSize().Width, pInfinityTexture->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw bar
	
}
void GameOverScreen::Draw(IVideoDriver* driver) {

	driver->draw2DImage(GameOverSprite,
		core::position2d<int>(0, 0),
		core::rect<int>(0, 0, GameOverSprite->getSize().Width, GameOverSprite->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw bar

}


