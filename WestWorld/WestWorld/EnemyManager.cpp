#include "EnemyManager.h"




EnemyManager::EnemyManager(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver)
{
	ismgr = smgr;
	iselector = selector;
	imeta = meta;
	idriver = driver;
}

void EnemyManager::CreateEnemy() {
	Enemy * test1 = new Enemy();
	test1->Init(ismgr, iselector, imeta, idriver);
	//enemyList.push_back(test1);
	enemyList.push_back(test1);
}

void EnemyManager::FillList(Enemy* enemy){
	// add enemy to list
	//enemyList.push_back(enemy);
	// GET ALL ENEMIES FROM SCENE OLD ////////////////////////////////////////////// REE
	//core::array<scene::ISceneNode *> nodes;
	//smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

	//for (u32 i = 0; i < nodes.size(); ++i)
	//{
	//	scene::ISceneNode * node = nodes[i];

	//	switch (node->getID())
	//	{
	//	case 17:
	//		enemyList.push_back(node);
	//		break;
	//	}
	//}
}

void EnemyManager::CheckCollision(scene::ISceneNode *hitObject) {
	imeta->addTriangleSelector(iselector);
	bool koekje = false;
	for (Enemy* item : enemyList) {
		if (hitObject == item->enemyNode()) {
			if (item->hp > 0) {
				item->Damage();
			}
			else {
			//	imeta->removeTriangleSelector(item->enemyNode.getTriangleSelector());
				//item->node->remove();
				item->node->setPosition(core::vector3df(25, 25, 25));
			}
		};
	}
}

EnemyManager::~EnemyManager()
{
}


Enemy::Enemy() {
}

void Enemy::Init(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::IMetaTriangleSelector* meta, video::IVideoDriver* driver) {
	
	scene::IMesh* barrelMesh = smgr->getMesh("meshes/Barrel.obj");
	node = smgr->addMeshSceneNode(barrelMesh, 0, 17);
	if (node)
	{
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
		node->setPosition(core::vector3df(19,19,19));
		selector = smgr->createTriangleSelector(node->getMesh(), node);
		node->setTriangleSelector(selector);
		meta->addTriangleSelector(selector);
		selector->drop();
		meta->drop();
	}
}

scene::IMeshSceneNode* Enemy::enemyNode() {
	return node;
}

void Enemy::Damage() {
	if (hp > 0)
		hp -= 1;
}


