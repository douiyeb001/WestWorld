#include "WaveManager.h"



WaveManager::WaveManager(CGameManager* pManager,PlayerBase* playerCore, Grid* grid, EnemyManager* enemyManager, Timer* enemyTimer):waveCount(1), p_Timer(enemyTimer)
{
	spawnPoints.push_back(new EnemySpawner(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, vector3df(0, 0, -350), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f), playerCore, grid, pManager->GetMeta(), enemyManager, enemyTimer));
	spawnPoints.push_back(new EnemySpawner(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, vector3df(400, 0, -200), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f), playerCore, grid, pManager->GetMeta(), enemyManager, enemyTimer));
	spawnPoints.push_back(new EnemySpawner(pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, vector3df(-400, 0, -200), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f), playerCore, grid, pManager->GetMeta(), enemyManager, enemyTimer));
}


WaveManager::~WaveManager()
{

}

void WaveManager::Update() {
	if (enemiesInWave > 0) {
		if (waveCount <= 1)
			spawnPoints[0]->SpawnOpponent();
		else
			spawnPoints[rand() % spawnPoints.size()]->SpawnOpponent();
		p_Timer->set(1000);
		enemiesInWave--;
	}
}

void WaveManager::NewWave(int enemies) {
	enemiesInWave = enemies * waveCount;
	p_Timer->set(1000);
}