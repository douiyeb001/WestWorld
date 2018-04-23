#include "EnemyManager.h"




EnemyManager::EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver)
{
	ismgr = smgr;
	iselector = selector;
	imeta = meta;
	idriver = driver;
}



void EnemyManager::FillList(Opponent* enemy){

	opponentList.push_back(enemy);


}

void EnemyManager::CheckCollision(scene::ISceneNode *hitObject) {
	imeta->addTriangleSelector(iselector);
	for (Opponent* item : opponentList) {
		if (hitObject == item) {
		
			{
				imeta->removeTriangleSelector(item->getTriangleSelector());
				item->item->remove();
			}
		};
	}
}

EnemyManager::~EnemyManager()
{
}





