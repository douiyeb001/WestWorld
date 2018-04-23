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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

GridCell::~GridCell()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Assign parent. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="_x">	   	The x coordinate. </param>
/// <param name="_y">	   	The y coordinate. </param>
/// <param name="goalX">   	The goal x coordinate. </param>
/// <param name="goalY">   	The goal y coordinate. </param>
/// <param name="_parent"> 	[in,out] If non-null, the parent. </param>
/// <param name="diagonal">	True to diagonal. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Estimate remaining cost. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="x">		The x coordinate. </param>
/// <param name="y">		The y coordinate. </param>
/// <param name="goalY">	The goal y coordinate. </param>
/// <param name="goalX">	The goal x coordinate. </param>
///
/// <returns>	An int. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int GridCell::EstimateRemainingCost(int x, int y, int goalY, int goalX) {
	return g + abs(goalX - x + goalY - y);
}