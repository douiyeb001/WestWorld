#include "GridCell.h"
#include <math.h>


/*
GridCell::GridCell(int _x, int _y, GridCell* _parent) : parent(NULL), pathToCell(), isFindingPath(true), g(0.0), f(0.0), x(_x),y(_y)
{
if (_parent) {
parent = _parent;
pathToCell = (*parent).pathToCell;
//1.414 for diagonal
g = parent->g+(Cell_Size *1);
f = g + EstimateRemainingCost(x,y,100,100);
}
pathToCell.push_back(parent);
}
*/

GridCell::~GridCell()
{
}

void GridCell::AssignParent(int _x, int _y, int goalX, int goalY, GridCell* _parent, bool diagonal) {

	if (_parent) {
		parent = _parent;
		pathToCell = (*parent).pathToCell;
		g = parent->g + (Cell_Size * (diagonal) ? 1.414 : 1);
	}
	//1.414 for diagonal 
	f = g + abs(goalX - x) + abs(goalY - y);
	isFindingPath = false;
	pathToCell.push_back(parent);
}

int GridCell::EstimateRemainingCost(int x, int y, int goalY, int goalX) {
	return g + abs(goalX - x + goalY - y);
}