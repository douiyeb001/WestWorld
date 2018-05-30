#pragma once
#include <map>
#include "GridCell.h"

class Grid
{
public:
	Grid(std::vector<bool> _obstacle);
	~Grid();
	/// <summary>	Key map of grid cells. </summary>
	std::map<int, GridCell> cellDictionary;


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Calculates the ID based on the coordinates. </summary>
	///
	/// <param name="x">	The x coordinate. </param>
	/// <param name="z">	The z coordinate. </param>
	///
	/// <returns>	Returns the id of the cell on the chosen position. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	int CoordinatesToID(int x, int z);

	std::vector<bool> obstacle;
};

