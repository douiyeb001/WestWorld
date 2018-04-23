#pragma once
#include <vector>

#define Cell_Size 10
#define World_Size 2000

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A grid cell. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class GridCell {
public:
	/// <summary>	The path to cell. </summary>
	std::vector<GridCell*> pathToCell;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the f and g. </summary>
	///
	/// <value>	The f and g values. </value>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	float f;
	float g;

	/// <summary>	The x coordinate. </summary>
	int x;
	/// <summary>	The y coordinate. </summary>
	int y;
	/// <summary>	True if is finding path, false if not. </summary>
	bool isFindingPath;
	/// <summary>	The parent. </summary>
	GridCell* parent;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	GridCell() :parent(0) {}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="_x">	   	The x coordinate. </param>
	/// <param name="_y">	   	The y coordinate. </param>
	/// <param name="_parent"> 	[in,out] If non-null, the parent. </param>
	/// <param name="occupied">	True if occupied. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	GridCell(int _x, int _y, GridCell* _parent, bool occupied) : parent((_parent) ? _parent : NULL), isFindingPath(!occupied), g(0.0), f(0.0), x(_x), y(_y), pathToCell((_parent) ? (*_parent).pathToCell : std::vector<GridCell*>(0)) {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~GridCell();

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

	void AssignParent(int _x, int _y, int goalX, int goalY, GridCell* _parent, bool diagonal);

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

	int EstimateRemainingCost(int x, int y, int goalY, int goalX);
};

