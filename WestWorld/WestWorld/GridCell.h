#pragma once
#include <vector>

#define Cell_Size 20
#define World_Size 2000

class GridCell {
public:
	std::vector<GridCell*> pathToCell;
	float f, g;
	int x, y;
	bool obstacle;
	bool isFindingPath;
	GridCell* parent;
	GridCell() :parent(0) {}
	GridCell(int _x, int _y, GridCell* _parent, bool occupied) : parent((_parent) ? _parent : NULL), obstacle(occupied), g(0.0), f(0.0), x(_x), y(_y), pathToCell((_parent) ? (*_parent).pathToCell : std::vector<GridCell*>(0)), isFindingPath(true) {};
	~GridCell();
	void AssignParent(int _x, int _y, int goalX, int goalY, GridCell* _parent, bool diagonal);
	int EstimateRemainingCost(int x, int y, int goalY, int goalX);
	void Clear();
};

