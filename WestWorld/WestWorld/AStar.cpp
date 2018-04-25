#include "AStar.h"
#include <map>


AStar::AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, std::vector<bool> Obstacle) {
	//bool test = Obstacle[0];
	//int test2 = coordinatesToID(25*Cell_Size, -100*Cell_Size);
	//CellDictionary = std::map<int, GridCell> (rint(World_Size / Cell_Size)*rint(World_Size / Cell_Size));
	for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
		for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
			CellDictionary.insert(std::pair<int, GridCell>(coordinatesToID(x*Cell_Size, z*Cell_Size), GridCell(x*Cell_Size + Cell_Size / 2, z*Cell_Size + Cell_Size / 2, NULL, Obstacle[coordinatesToID(x*Cell_Size, z*Cell_Size)])));
	//CellDictionary[coordinatesToID(x,z)] = GridCell(x,z,NULL);

	int xcoord = startNode_->getAbsolutePosition().X;
	int zcoord = startNode_->getAbsolutePosition().Z;

	possibleNextCells.reserve((rint(World_Size / Cell_Size) * rint(World_Size / Cell_Size)));
	startCell = &(CellDictionary[coordinatesToID(xcoord, zcoord)]);
	possibleNextCells.push_back(startCell);


	int xcoordGoal = goalNode_->getAbsolutePosition().X;
	int zcoordGoal = goalNode_->getAbsolutePosition().Z;

	(CellDictionary[coordinatesToID(xcoord, zcoord)]).AssignParent(xcoord, zcoord, xcoordGoal, zcoordGoal, NULL, false);
	goalCell = &CellDictionary[coordinatesToID(xcoordGoal, zcoordGoal)];

	findPath();
}


AStar::~AStar() {

}


GridCell* AStar::nextCell() {

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
		//(*nextCell).isFindingPath = false;
		possibleNextCells.erase(possibleNextCells.begin() + idx);
	}

	return nextCell;
}

void AStar::findPath() {
	GridCell* currentCell = nextCell();

	if (currentCell == goalCell) {
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
				int id = coordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2);
				bool test = (CellDictionary[coordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath;
				if ((CellDictionary[coordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).isFindingPath && !(CellDictionary[coordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]).obstacle) {
					(CellDictionary[coordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)].AssignParent(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2, goalCell->x, goalCell->y, currentCell, (abs(x) == abs(z))));
					possibleNextCells.push_back(&(CellDictionary[coordinatesToID(xPos + x * Cell_Size - Cell_Size / 2, yPos + z * Cell_Size - Cell_Size / 2)]));
				}
			}
		}
	}

	findPath();
}


void AStar::RecalculatePath(core::vector3df spawnedPosition) {
	CellDictionary[coordinatesToID(spawnedPosition.X, spawnedPosition.Z)].obstacle = true;
	//if (std::find(std::begin(currentPath), std::end(currentPath), (&(CellDictionary[coordinatesToID(spawnedPosition.X, spawnedPosition.Z)]))) != std::end(currentPath)) {
	for (int x = -((World_Size / Cell_Size) / 2); x < (World_Size / Cell_Size) / 2; x++)
		for (int z = -((World_Size / Cell_Size) / 2); z < (World_Size / Cell_Size) / 2; z++)
			CellDictionary[coordinatesToID(x*Cell_Size, z*Cell_Size)].Clear();

	possibleNextCells.push_back(startCell);
		findPath();
	//}
}

std::vector<GridCell*> AStar::ReversePath(std::vector<GridCell*> path) {
	std::vector<GridCell*> reversedPath;
	for (int i = path.size() -1 ; i > 0; i--)
		reversedPath.push_back(path[i]);
	return reversedPath;
}

int AStar::coordinatesToID(int x, int z) {
	int test = ((x / Cell_Size) + World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size) + World_Size / (2 * Cell_Size));
	return ((x / Cell_Size) + World_Size / (2 * Cell_Size)) * (World_Size / Cell_Size) + ((z / Cell_Size) + World_Size / (2 * Cell_Size));
	//return (x / Cell_Size)*World_Size + (World_Size / Cell_Size * World_Size / Cell_Size) / 2 + (z / Cell_Size) + (World_Size / Cell_Size) / 10;
}

core::vector3df AStar::getCentre(core::vector3df position) {
	core::vector3df centre = position;
	centre.X = CellDictionary[coordinatesToID(position.X, position.Z)].x;
	centre.Z = CellDictionary[coordinatesToID(position.X, position.Z)].y;
	return centre;
}
/*irr::core::vector3df AStar::NextPathPosition(irr::core::vector3df pos, float speed)
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

	distance.normalize();

	return (pos + speed * distance);
}*/