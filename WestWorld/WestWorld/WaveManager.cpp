#include "WaveManager.h"
#include <numeric>

#include <irrKlang-64bit-1.6.0/include/ik_ISoundEngine.h>

irrklang::ISoundEngine* iSoundEngine;


WaveManager::WaveManager(irrklang::ISoundEngine* SoundEngine, CGameManager* pManager,PlayerBase* playerCore, Grid* grid, EnemyManager* enemyManager, Timer* enemyTimer):waveCount(1), p_Timer(enemyTimer)
{
	iSoundEngine = SoundEngine;
	spawnPoints.push_back(new EnemySpawner(iSoundEngine,pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, vector3df(0, 0, -350), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f), playerCore, grid, pManager->GetMeta(), enemyManager, enemyTimer));
	spawnPoints.push_back(new EnemySpawner(iSoundEngine, pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, vector3df(400, 0, -200), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f), playerCore, grid, pManager->GetMeta(), enemyManager, enemyTimer));
	spawnPoints.push_back(new EnemySpawner(iSoundEngine, pManager->getSceneManager()->getMesh("meshes/Barrel.obj"), pManager->getSceneManager()->getRootSceneNode(), pManager->getSceneManager(), -2, vector3df(-400, 0, -200), vector3df(0, 0, 0), vector3df(1.0f, 1.0f, 1.0f), playerCore, grid, pManager->GetMeta(), enemyManager, enemyTimer));

	for (int i = 1; i < 6; i++) {
		vector<int> enemies; //1e waarde is midden, 2e waarde is links, 3e waarde is rechts
		int x;
		switch (i) {
		case 1:
			enemies = { 5,0,0 };
			break;
		case 2:
			enemies = { 0,10,0 };
			break;
		case 3:
			x = rand() % 15;
			enemies = { x,15-x,0 };
			break;
		case 4:
			enemies = { 5+ rand()%5,5 + rand() % 5,5 + rand() % 5 };
			break;
		case 5:
			enemies = { 10 + rand() % 10,10 + rand() % 10,10 + rand() % 10 };
			break;
		case 6:
			enemies = { 1,1,1 };
			break;
		}
		//= { (i % 1 == 1 ? 5 : 0),(i % 1 == 0 ? 5 : 0), (i > 2 && i % 1 == 0 ? 5 : 0) };
		waveSpawns.insert(std::pair<int, vector<int>>(i, enemies));
	}
}


WaveManager::~WaveManager()
{

}

void WaveManager::Update() {
	if (enemiesInWave > 0) {
		int spawnedOnPoint = spawned;
		for (int i = 0; i < 3; i++) {
			if (waveSpawns[waveCount][i] > spawnedOnPoint) {
				(*spawnPoints[i]).SpawnOpponent();
				enemiesInWave--;
				spawned++;
				if (enemiesInWave > 0)
				p_Timer->set(1000);
				return;
			}
			else
				spawnedOnPoint -= waveSpawns[waveCount][i];
		}
	}
}

void WaveManager::NewWave() {
	enemiesInWave = std::accumulate(waveSpawns[waveCount].begin(), waveSpawns[waveCount].end(), 0);
	spawned = 0;
	p_Timer->set(1000);
}