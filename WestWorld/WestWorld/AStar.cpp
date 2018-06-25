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

AStar::AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, Grid* _grid) : grid(_grid) {
	//bool test = Obstacle[0];
	//int test2 = CoordinatesToID(25*Cell_Size, -100*Cell_Size);
	//CellDictionary = std::map<int, GridCell> (rint(World_Size / Cell_Size)*rint(World_Size / Cell_Size));
	//CellDictionary[CoordinatesToID(x,z)] = GridCell(x,z,NULL);
	cellsPassed = 0;

	int xcoord = startNode_->getAbsolutePosition().X;
	int zcoord = startNode_->getAbsolutePosition().Z;

	possibleNextCells.reserve((rint(World_Size / Cell_Size) * rint(World_Size / Cell_Size)) * 100);
	pStartCell = &((*grid).cellDictionary[(*grid).CoordinatesToID(xcoord, zcoord)]);
	possibleNextCells.push_back(pStartCell);


	int xcoordGoal = goalNode_->getAbsolutePosition().X;
	int zcoordGoal = goalNode_->getAbsolutePosition().Z;

	((*grid).cellDictionary[(*grid).CoordinatesToID(xcoord, zcoord)]).AssignParent(xcoord, zcoord, xcoordGoal, zcoordGoal, NULL, false);
	pGoalCell = &(*grid).cellDictionary[(*grid).CoordinatesToID(xcoordGoal, zcoordGoal)];

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
	if (possibleNextCells.empty() || cellsPassed > maxCells) {
		for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
			for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
				(*grid).cellDictionary[(*grid).CoordinatesToID(x*Cell_Size, z*Cell_Size)].Clear();
		return;
	}
	GridCell* currentCell = NextCell();

	if (currentCell == pGoalCell) {
		if (initialPath.size() == 0)
			initialPath = ReversePath(currentCell->pathToCell);
		currentPath = ReversePath(currentCell->pathToCell);

		for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
			for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
				(*grid).cellDictionary[(*grid).CoordinatesToID(x*Cell_Size, z*Cell_Size)].Clear();
		return;
	}
	int xPos = currentCell->x;
	int yPos = currentCell->y;
	/*std::vector<std::pair<int, int>> borderingCells;
	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 1; z++) {
			if ((x != 0 || z != 0)) {
				int id = CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2);
				bool test = (cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath;
				if ((cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath && !(cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).obstacle) {
					(cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)].AssignParent(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2, pGoalCell->x, pGoalCell->y, currentCell, (abs(x) == abs(z))));
					borderingCells.emplace_back(std::pair<int, int>(x, z));
				}
			}
		}
	}*/
	/*
	bool possibleCell[9];
	
	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 1; z++) {
			if ((x != 0 || z != 0)) {
				int id = CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2);
				bool test = (cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath;
				if ((cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath && !(cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).obstacle) {
					(cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)].AssignParent(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2, pGoalCell->x, pGoalCell->y, currentCell, (abs(x) == abs(z))));
					possibleCell[(x + 1) * 3 + (z + 1)] = true;
				} else {
					possibleCell[(x + 1) * 3 + (z + 1)] = false;
				}

			}
			else {
				possibleCell[(x + 1) * 3 + (z + 1)] = false;
			}
		}
	}*/

	/*if (possibleCell[0])
		possibleCell[0] = false;

	if (possibleCell[2])
		possibleCell[2] = false;

	if (possibleCell[6])
		possibleCell[6] = false;

	if (possibleCell[8])
		possibleCell[8] = false;
	
	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 1; z++) {
			if ((x != 0 || z != 0)) {
				if (possibleCell[(x + 1) * 3 + (z + 1)])
					possibleNextCells.push_back(&(cellDictionary[CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]));
				}
			}
		}

	/*for (int i = 0; i < borderingCells.size();i++) {
		if (abs(borderingCells[i].first) + abs(borderingCells[i].second) == 2)
			if (std::find(borderingCells.begin(), borderingCells.end(), std::pair<int, int>(borderingCells[i].first, 0)) != borderingCells.end() || std::find(borderingCells.begin(), borderingCells.end(), std::pair<int, int>(0, borderingCells[i].second)) != borderingCells.end())
			{
				possibleNextCells.push_back(&(cellDictionary[CoordinatesToID(xPos + borderingCells[i].first * Cell_Size - Cell_Size / 2, yPos + borderingCells[i].second * Cell_Size - Cell_Size / 2)]));
			}
	}*/

	for (int x = -1; x <= 1; x++) {
		for (int z = -1; z <= 1; z++) {
			//if ((x != 0 || z != 0)) {
			if (abs(x)!=abs(z)){
				int id = (*grid).CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2);
				bool test = ((*grid).cellDictionary[(*grid).CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath;
				if (((*grid).cellDictionary[(*grid).CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath && !((*grid).cellDictionary[(*grid).CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).obstacle) {
					((*grid).cellDictionary[(*grid).CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)].AssignParent(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2, pGoalCell->x, pGoalCell->y, currentCell, (abs(x) == abs(z))));
					possibleNextCells.push_back(&((*grid).cellDictionary[(*grid).CoordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]));
				}
			}
		}
	}
	cellsPassed++;
	FindPath();
}


bool AStar::RecalculatePath(core::vector3df spawnedPosition) {
	cellsPassed = 0;
	SetObstacle(true, spawnedPosition);
	//(*grid).cellDictionary[(*grid).CoordinatesToID(spawnedPosition.X, spawnedPosition.Z)].obstacle = true;
	if (std::find(std::begin(currentPath), std::end(currentPath), (&((*grid).cellDictionary[(*grid).CoordinatesToID(spawnedPosition.X, spawnedPosition.Z)]))) != std::end(currentPath)) {

		possibleNextCells.clear();
		possibleNextCells.push_back(pStartCell);
		FindPath();
		if (possibleNextCells.empty() || cellsPassed > maxCells) {
			SetObstacle(false, spawnedPosition);
			//(*grid).cellDictionary[(*grid).CoordinatesToID(spawnedPosition.X, spawnedPosition.Z)].obstacle = false;
			return false;
		}
	}
	return true;
}

void AStar::SetObstacle(bool filled, core::vector3df position) {
	(*grid).cellDictionary[(*grid).CoordinatesToID(position.X, position.Z)].obstacle = filled;
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



core::vector3df AStar::GetCentre(core::vector3df position) {
	core::vector3df centre = position;
	centre.X = (*grid).cellDictionary[(*grid).CoordinatesToID(position.X, position.Z)].x;
	centre.Z = (*grid).cellDictionary[(*grid).CoordinatesToID(position.X, position.Z)].y;
	return centre;
}

GridCell* AStar::GetCell(core::vector3df position) {
	return &(*grid).cellDictionary[(*grid).CoordinatesToID(position.X, position.Z)];
}

std::vector<GridCell*> AStar::GetSurroundingCells(core::vector3df position) {
	core::vector3df centre = GetCentre(position);
	std::vector<GridCell*> cells;
	for (int x = -1; x <= 1; x++) 
		for (int z = -1; z <= 1; z++) 
				cells.push_back(&(*grid).cellDictionary[(*grid).CoordinatesToID(centre.X + ((x)* Cell_Size) - Cell_Size, centre.Z + ((z) * Cell_Size)-Cell_Size)]);
	return cells;
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