#include "SetupHUD.h"

SetupHUD::SetupHUD(IVideoDriver* driver){
	createHUD(driver);
}



void SetupHUD::createHUD(IVideoDriver* driver) {
	hp = new HealthBar(driver, "media/UI/HealthBarDefinitelyNotStolen.png");
	icon1 = new Placeable(driver, "media/UI/towerIcon.png");
	icon2 = new Placeable(driver, "media/UI/trapIcon.png");
	icon3 = new Placeable(driver, "media/UI/cannonIcon.png");
	//icon1->Draw(driver);
	//icon2->Draw(driver);
	//icon3->Draw(driver);
	DrawAll(driver, hp, icon1, icon2, icon3);
}

void SetupHUD::DrawAll(IVideoDriver* driver, HealthBar* hp, Placeable* icon1, Placeable* icon2, Placeable* icon3) {
	hp->Draw(driver);
	icon1->Draw(driver);
	icon2->Draw(driver);
	icon3->Draw(driver);
}
