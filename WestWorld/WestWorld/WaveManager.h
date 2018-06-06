#pragma once
#include "enemySpawner.h"
#include "GameManager.h"
#include "Grid.h"
#include "EnemyManager.h"
#include "Timer.h"

class WaveManager
{
public:
	WaveManager(CGameManager* pManager, PlayerBase* playerCore, Grid* grid, EnemyManager* enemyManager, Timer* enemyTimer);
	~WaveManager();
	int waveCount;
	std::vector<EnemySpawner*> spawnPoints;
	void Update();
	void NewWave(int enemies);
	int enemiesInWave;
	Timer* p_Timer;
};

