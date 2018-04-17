#include "EnemyManager.h"




EnemyManager::EnemyManager()
{
	
}

void EnemyManager::FillList(scene::ISceneManager* smgr) {
	core::array<scene::ISceneNode *> nodes;
	smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

	for (u32 i = 0; i < nodes.size(); ++i)
	{
		scene::ISceneNode * node = nodes[i];

		switch (node->getID())
		{
		case 17:
			test.push_back(node);
			break;
		}
	}

	//test.push_back(meme);
}

void EnemyManager::CheckCollision(scene::ISceneNode* test) {
	//for(int i = 0; i < test.size)
}

EnemyManager::~EnemyManager()
{
}
