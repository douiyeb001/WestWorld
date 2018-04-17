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
	std::vector<GridCell*> finalPath;

	AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, bool Obstacle[(World_Size / Cell_Size)*(World_Size / Cell_Size)]);
	~AStar();
	void findPath();
	std::vector<GridCell*> ReversePath(std::vector<GridCell*>);
	GridCell* nextCell();
	GridCell* goalCell;
	int coordinatesToID(int x, int z);
	core::vector3df NextPathPosition(irr::core::vector3df pos, float speed);
};

