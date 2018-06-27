#include "Grid.h"



Grid::Grid(std::vector<bool> _obstacle) : obstacle(_obstacle)
{
	for (int x = -((World_Size / Cell_Size) / 2) + 1; x < (World_Size / Cell_Size) / 2; x++)
		for (int z = -((World_Size / Cell_Size) / 2) + 1; z < (World_Size / Cell_Size) / 2; z++)
			cellDictionary.insert(std::pair<int, GridCell>(CoordinatesToID(x*Cell_Size, z*Cell_Size), GridCell(x*Cell_Size + Cell_Size / 2, z*Cell_Size + Cell_Size / 2, NULL, obstacle[CoordinatesToID(x*Cell_Size, z*Cell_Size)])));
}


Grid::~Grid()
{
}

const int Grid::CoordinatesToID(int x, int z) {
	int test= ((x)+World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z)+World_Size / (2 * Cell_Size));
	return  ((x/Cell_Size)+World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size)+World_Size / (2 * Cell_Size));
	//return ((x / Cell_Size) * (World_Size / Cell_Size) + ((z / Cell_Size))) + (2* (World_Size / Cell_Size) -1);
	// number x adjusted to start at 0 times total y plus number y adjusted to start at 0
}
