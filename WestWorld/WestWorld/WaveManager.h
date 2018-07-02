#pragma once
#include "enemySpawner.h"
#include "GameManager.h"
#include "Grid.h"
#include "EnemyManager.h"
#include "Timer.h"

class WaveManager
{
public:
	WaveManager(irrklang::ISoundEngine* SoundEngine, CGameManager* pManager, PlayerBase* playerCore, Grid* grid, EnemyManager* enemyManager, Timer* enemyTimer);
	~WaveManager();
	int waveCount;
	std::vector<EnemySpawner*> spawnPoints;
	void Update();
	void NewWave();
	int enemiesInWave;
	int spawned;
	Timer* p_Timer;
	std::map<int, vector<int>> waveSpawns;
};

