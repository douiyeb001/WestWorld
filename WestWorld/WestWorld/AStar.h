#pragma once
#include <irrlicht.h>
#include <vector3d.h>
#include <vector>
#include <map>
#include "SearchGrid.h"
#include "GridCell.h"
#include <math.h>

using namespace irr;

class AStar
{
public:
	std::map<int, GridCell> CellDictionary;
	std::vector<GridCell*> possibleNextCells;
	std::vector<GridCell*> initialPath;
	std::vector<GridCell*> currentPath;

	AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, std::vector<bool> Obstacle);
	~AStar();
	void findPath();
	std::vector<GridCell*> ReversePath(std::vector<GridCell*> path);
	void RecalculatePath(core::vector3df spawnedPosition);
	GridCell* nextCell();
	GridCell* startCell;
	GridCell* goalCell;
	GridCell* targetCell;
	int coordinatesToID(int x, int z);
	core::vector3df getCentre(core::vector3df position);
	//core::vector3df NextPathPosition(irr::core::vector3df pos, float speed);
};

