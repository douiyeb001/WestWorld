#include "EnemyManager.h"




EnemyManager::EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver, Currency* _cManager)
{
	ismgr = smgr;
	iselector = selector;
	imeta = meta;
	idriver = driver;
	cManager = _cManager;
}

void EnemyManager::Update() {
	// update all the enemies
	for (Opponent* op : opponentList) {
		op->Update();
	}

	// give turret ai list of enemies ~ events / not in update next version
	

}


vector<Opponent*> EnemyManager::GiveArray()
{
	return opponentList;
}

void EnemyManager::FillList(Opponent* enemy){
	opponentList.push_back(enemy);
}

void EnemyManager::CheckCollision(scene::ISceneNode *hitObject) {
	//imeta->addTriangleSelector(iselector);
	for (int i = 0; i < opponentList.size(); i++) {
		if (hitObject == opponentList[i])
			{
				imeta->removeTriangleSelector(opponentList[i]->getTriangleSelector());
				opponentList[i]->remove();
				opponentList.erase(opponentList.begin() + i);
				cManager->EnemyCurrency();
			}
	}

	//for (Opponent* item : opponentList) {
	//	if (hitObject == item) {
	//	
	//		{
	//			imeta->removeTriangleSelector(item->getTriangleSelector());
	//			item->remove();
	//			opponentList.remove(opponentList.);
	//		}
	//	};
	//}
}
void EnemyManager::RemoveFromArray(scene::ISceneNode* turretOpponent) {
	for (int i = 0; i < opponentList.size(); i++) {
		if (opponentList[i] == turretOpponent)
		{


			imeta->removeTriangleSelector(opponentList[i]->getTriangleSelector());
			opponentList[i]->remove();
			opponentList.erase(opponentList.begin() + i);
			cManager->EnemyCurrency();
			
		}
		
	}
}
EnemyManager::~EnemyManager()
{
}





