#include "EnemyManager.h"




EnemyManager::EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver)
{
	ismgr = smgr;
	iselector = selector;
	imeta = meta;
	idriver = driver;
}

void EnemyManager::Update() {
	// update all the enemies
	for (Opponent* op : opponentList) {
		op->Update();
	}

	// give turret ai list of enemies ~ events / not in update next version


}



void EnemyManager::FillList(Opponent* enemy){
	opponentList.push_back(enemy);
}

void EnemyManager::CheckCollision(scene::ISceneNode *hitObject) {
	//imeta->addTriangleSelector(iselector);
	for (Opponent* item : opponentList) {
		if (hitObject == item) {
		
			{
				imeta->removeTriangleSelector(item->getTriangleSelector());
				item->remove();
			}
		};
	}
}

EnemyManager::~EnemyManager()
{
}





