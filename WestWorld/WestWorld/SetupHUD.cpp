#include "SetupHUD.h"

SetupHUD::SetupHUD(){

}

void SetupHUD::createHUD(IVideoDriver* driver) {
	hp = new HealthBar(driver, "media/UI/HealthBarDefinitelyNotStolen.png");
	hp->Draw(driver);
	icon1 = new Placeable(driver, "media/UI/towerIcon.png");
	icon2 = new Placeable(driver, "media/UI/trapIcon.png");
	icon3 = new Placeable(driver, "media/UI/cannonIcon.png");
	icon1->Draw(driver);
	icon2->Draw(driver);
	icon3->Draw(driver);
}
