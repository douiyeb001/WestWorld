 #include "GUIBase.h"
#include <stdio.h> 

PlayerHealthBar::PlayerHealthBar(IVideoDriver* driver, char const* bar) {
	hpBar = driver->getTexture(bar);
	driver->makeColorKeyTexture(hpBar, core::position2d<s32>(0, 0));
}

void PlayerHealthBar::Draw(IVideoDriver* driver) {
	driver->draw2DImage(hpBar, core::position2d<int>(driver->getScreenSize().Width - hpBar->getSize().Width - 25, 10 ), core::rect<int>(0, 0, hpBar->getSize().Width, hpBar->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
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


void Reticle::Draw(IVideoDriver* driver) {
	driver->draw2DImage(reticleSprite, core::position2d<int>((driver->getScreenSize().Width - reticleSprite->getSize().Width )/2, (driver->getScreenSize().Height - reticleSprite->getSize().Height)/2), core::rect<int>(0, 0, reticleSprite->getSize().Width, reticleSprite->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw shooting reticle
}

CurrencyUI::CurrencyUI(IVideoDriver* driver, char const* pDollar, char const* pInfinity) {
	//font = device->getGUIEnvironment()->getFont("medi.bmp");
	//pScore = (const wchar_t*)cager->playerCurrency;
	pDollarTexture = driver->getTexture(pDollar);
	pInfinityTexture = driver->getTexture(pInfinity);

}
GameOverScreen::GameOverScreen(IVideoDriver* driver, char const* deadLogo){
	GameOverSprite = driver->getTexture(deadLogo);


}
VictoryScreen::VictoryScreen(IVideoDriver* driver, char const* victoryLogo) {
	VictorySprite = driver->getTexture(victoryLogo);


}
WaveCounterUI::WaveCounterUI(IVideoDriver* pDriver, IGUIEnvironment* pGui)
{
	pFont = pGui->getFont("media/bigfont.png");
}
void WaveCounterUI::Draw(IGUIEnvironment* pGui, IVideoDriver* pDriver, int waveNumber)
{
	
	pFont->draw((L"%d", (stringc)waveNumber),
			core::rect<s32>(1150, 180, 500, 500),
			video::SColor(255, 0, 0, 0));
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
		core::position2d<int>(10, driver->getScreenSize().Height - pDollarTexture->getSize().Height - 10), 
		core::rect<int>(0, 0, pDollarTexture->getSize().Width, pDollarTexture->getSize().Height), 
		0, 
		video::SColor(255, 255, 255, 255), true); //Draw bar

	driver->draw2DImage(pInfinityTexture,
		core::position2d<int>(80, driver->getScreenSize().Height - pInfinityTexture->getSize().Height + 10),
		core::rect<int>(0, 0, pInfinityTexture->getSize().Width, pInfinityTexture->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw bar
	
}
void GameOverScreen::Draw(IVideoDriver* driver) {

	driver->draw2DImage(GameOverSprite,
		core::position2d<int>(0, 0),
		core::rect<int>(0, 0, GameOverSprite->getSize().Width, GameOverSprite->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw game over sprite
}
void VictoryScreen::Draw(IVideoDriver* driver) {
	
		driver->draw2DImage(VictorySprite,
		core::position2d<int>(0, 0),
		core::rect<int>(0, 0, VictorySprite->getSize().Width, VictorySprite->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw victory screen sprite
}

WaveCounter::WaveCounter(IVideoDriver* driver, char const* bar) {
	pWaveImage = driver->getTexture(bar);
	driver->makeColorKeyTexture(pWaveImage, core::position2d<s32>(0, 0));
}

void WaveCounter::Draw(IVideoDriver* driver)
{
	driver->draw2DImage(pWaveImage, core::position2d<int>(driver->getScreenSize().Width - pWaveImage->getSize().Width, 100),
	core::rect<int>(-25, -40, pWaveImage->getSize().Width, pWaveImage->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}			

DrawUI::DrawUI(IVideoDriver* driver)
{
	

	pPlayerHealthBar = new PlayerHealthBar(driver, "media/UI/playerHealth (Custom).png");
	pCurrencyUI = new CurrencyUI(driver, "media/UI/rsz_1dollar.png", "media/UI/rsz_1rsz_infinity.png");
	pReticle = new Reticle(driver, "media/UI/rsz_reticle.png");
	pWaveCounter = new WaveCounter(driver, "media/UI/waveCounter (Custom).png");
}

void DrawUI::Draw(IVideoDriver* driver, IGUIEnvironment* gui) {
	pPlayerHealthBar->Draw(driver);
	pCurrencyUI->Draw(gui, driver);
	pReticle->Draw(driver);
	pWaveCounter->Draw(driver);

}

