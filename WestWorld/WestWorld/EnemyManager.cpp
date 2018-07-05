#include "EnemyManager.h"



EnemyManager::EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver, Currency* _cManager, Timer* pTimer) : p_Timer(pTimer)
{
	ismgr = smgr;
	iselector = selector;
	imeta = meta;
	idriver = driver;
	cManager = _cManager;
}

void EnemyManager::Update(std::vector<GridCell*> PlayerRange, IDamagable* pPlayer) {
	// update all the enemies
 	int deltaTime = p_Timer->deltaTime();
	for (Opponent* op : opponentList) {
		if (op->isExploding){
			op->Update(deltaTime);
		}
		else if (std::find(PlayerRange.begin(), PlayerRange.end(), op->path[op->path.size() - op->pathProgress]) != PlayerRange.end()) {
			op->target = pPlayer;
			op->isExploding = true;
			//op->targetPos = playerPos; 
		}
		else {
			op->Update(deltaTime);
		}
	}
	RemoveFromArray();
	// give turret ai list of enemies ~ events / not in update next version
	

}


vector<Opponent*> EnemyManager::GiveArray()
{
	return opponentList;
}

void EnemyManager::FillList(Opponent* enemy){
	opponentList.push_back(enemy);
}

void EnemyManager::UpdatePath(std::vector<GridCell*> newPath, GridCell* changedCell) {
	for (int i = 0; i < opponentList.size(); i++) {
		opponentList[i]->ChangePath( newPath, changedCell);
	}
}


bool EnemyManager::CheckCollision(scene::ISceneNode *hitObject) {
	//imeta->addTriangleSelector(iselector);

	for (int i = 0; i < opponentList.size(); i++) {
		
		if (hitObject == opponentList[i])
		{
				imeta->removeTriangleSelector(opponentList[i]->getTriangleSelector());
				opponentList[i]->target = NULL;
				opponentList[i]->Damaged(1);
				
				//isHit = false;
				return true;
			}
	}
			 return false;

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

void EnemyManager::ToRemoveAfterUpdate(scene::ISceneNode* turretOpponent) {
	ToRemove.push_back(turretOpponent);
}

void EnemyManager::RemoveFromArray() {
	for (ISceneNode* op : ToRemove)
	for (int i = 0; i < opponentList.size(); i++) {
		if (opponentList[i] == op)
		{
			imeta->removeTriangleSelector(opponentList[i]->getTriangleSelector());
			opponentList[i]->remove();
			opponentList.erase(opponentList.begin() + i);
			cManager->EnemyCurrency();
			
		}
		
	}
	ToRemove.clear();
}
EnemyManager::~EnemyManager()
{
}





