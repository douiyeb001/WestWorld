#include "Grid.h"



Grid::Grid(std::vector<bool> _obstacle) : obstacle(_obstacle)
{
	for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
		for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
			cellDictionary.insert(std::pair<int, GridCell>(CoordinatesToID(x*Cell_Size, z*Cell_Size), GridCell(x*Cell_Size + Cell_Size / 2, z*Cell_Size + Cell_Size / 2, NULL, obstacle[CoordinatesToID(x*Cell_Size, z*Cell_Size)])));
}


Grid::~Grid()
{
}

int Grid::CoordinatesToID(int x, int z) {
	/// <summary>	The test. </summary>
	int test = ((x / Cell_Size) + World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size) + World_Size / (2 * Cell_Size));
	return ((x / Cell_Size) + World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size) + World_Size / (2 * Cell_Size));
	//return (x / Cell_Size)*World_Size + (World_Size / Cell_Size * World_Size / Cell_Size) / 2 + (z / Cell_Size) + (World_Size / Cell_Size) / 10;
}
