#include "AStar.h"
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="startNode_">	[in,out] If non-null, the start node. </param>
/// <param name="goalNode_"> 	[in,out] If non-null, the goal node. </param>
/// <param name="Obstacle">  	True to obstacle. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

AStar::AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, std::vector<bool> Obstacle) {
	//bool test = Obstacle[0];
	//int test2 = CoordinatesToID(25*Cell_Size, -100*Cell_Size);
	//CellDictionary = std::map<int, GridCell> (rint(World_Size / Cell_Size)*rint(World_Size / Cell_Size));
	for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
		for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
			CellDictionary.insert(std::pair<int, GridCell>(CoordinatesToID(x*Cell_Size, z*Cell_Size), GridCell(x*Cell_Size + Cell_Size / 2, z*Cell_Size + Cell_Size / 2, NULL, Obstacle[CoordinatesToID(x*Cell_Size, z*Cell_Size)])));
	//CellDictionary[CoordinatesToID(x,z)] = GridCell(x,z,NULL);

	int xcoord = startNode_->getAbsolutePosition().X;
	int zcoord = startNode_->getAbsolutePosition().Z;

	possibleNextCells.reserve((rint(World_Size / Cell_Size) * rint(World_Size / Cell_Size)));
	pStartCell = &(CellDictionary[CoordinatesToID(xcoord, zcoord)]);
	possibleNextCells.push_back(pStartCell);


	int xcoordGoal = goalNode_->getAbsolutePosition().X;
	int zcoordGoal = goalNode_->getAbsolutePosition().Z;

	(CellDictionary[CoordinatesToID(xcoord, zcoord)]).AssignParent(xcoord, zcoord, xcoordGoal, zcoordGoal, NULL, false);
	pGoalCell = &CellDictionary[CoordinatesToID(xcoordGoal, zcoordGoal)];

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Calls the FindPath() function. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	FindPath();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

AStar::~AStar() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Next cell. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else a pointer to a GridCell. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

GridCell* AStar::NextCell() {

	float bestF = 999999.0f;

	GridCell* nextCell = NULL;
	int idx = -1;

	for (int i = 0; i < possibleNextCells.size(); i++)
		if ((*possibleNextCells[i]).f < bestF) {
			nextCell = possibleNextCells[i];
			bestF = (*possibleNextCells[i]).f;
			idx = i;
		}

	if (idx >= 0) {
		//(*NextCell).isFindingPath = false;
		possibleNextCells.erase(possibleNextCells.begin() + idx);
	}

	return nextCell;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first path. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void AStar::FindPath() {
	GridCell* currentCell = NextCell();

	if (currentCell == pGoalCell) {
		possibleNextCells.clear();
		if (initialPath.size() == 0)
			initialPath = ReversePath(currentCell->pathToCell);
		currentPath = ReversePath(currentCell->pathToCell);
		return;
	}
	if (possibleNextCells.size() > 2000)
		int te = 0;
	int xPos = currentCell->x;
	int yPos = currentCell->y;
	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 1; z++) {
			if ((x != 0 || z != 0)) {
				int id = CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2);
				bool test = (CellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath;
				if ((CellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath && !(CellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).obstacle) {
					(CellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)].AssignParent(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2, pGoalCell->x, pGoalCell->y, currentCell, (abs(x) == abs(z))));
					possibleNextCells.push_back(&(CellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]));
				}
			}
		}
	}

	FindPath();
}


void AStar::RecalculatePath(core::vector3df spawnedPosition) {
	CellDictionary[CoordinatesToID(spawnedPosition.X, spawnedPosition.Z)].obstacle = true;
	//if (std::find(std::begin(currentPath), std::end(currentPath), (&(CellDictionary[CoordinatesToID(spawnedPosition.X, spawnedPosition.Z)]))) != std::end(currentPath)) {
	for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
		for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
			CellDictionary[CoordinatesToID(x*Cell_Size, z*Cell_Size)].Clear();

	possibleNextCells.push_back(pStartCell);
		FindPath();
	//}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reverse path. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="path">	[in,out] If non-null, full pathname of the file. </param>
///
/// <returns>	Null if it fails, else a std::vector&lt;GridCell*&gt; </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<GridCell*> AStar::ReversePath(std::vector<GridCell*> path) {
	std::vector<GridCell*> reversedPath;
	for (int i = path.size() -1 ; i > 0; i--)
		reversedPath.push_back(path[i]);
	return reversedPath;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Coordinates to identifier. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="x">	The x coordinate. </param>
/// <param name="z">	The z coordinate. </param>
///
/// <returns>	An int. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int AStar::CoordinatesToID(int x, int z) {
	/// <summary>	The test. </summary>
	int test = ((x / Cell_Size) + World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size) + World_Size / (2 * Cell_Size));
	return ((x / Cell_Size) + World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size) + World_Size / (2 * Cell_Size));
	//return (x / Cell_Size)*World_Size + (World_Size / Cell_Size * World_Size / Cell_Size) / 2 + (z / Cell_Size) + (World_Size / Cell_Size) / 10;
}

core::vector3df AStar::GetCentre(core::vector3df position) {
	core::vector3df centre = position;
	centre.X = CellDictionary[CoordinatesToID(position.X, position.Z)].x;
	centre.Z = CellDictionary[CoordinatesToID(position.X, position.Z)].y;
	return centre;
}
/*irr::core::vector3df AStar::NextPathPosition(irr::core::vector3df pos, float speed)
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Next path position. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="pos">  	The position. </param>
/// <param name="speed">	The speed. </param>
///
/// <returns>	An irr::core::vector3df. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

irr::core::vector3df AStar::NextPathPosition(irr::core::vector3df pos, float speed)
{
	if (finalPath.size() == 0)
		return pos;
	int index = 1;

	irr::core::vector3df nextPos;

	nextPos.X = finalPath[finalPath.size() - index]->x;
	nextPos.Z = finalPath[finalPath.size() - index]->y;

	irr::core::vector3df distance = nextPos - pos;

	if (distance.getLength() < 12)
	{
		finalPath.erase(finalPath.end() - index);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	The normalized distance. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	distance.normalize();

	return (pos + speed * distance);
}*/