#pragma once
#include <irrlicht.h>
#include <vector3d.h>
#include <vector>
#include <map>
#include "SearchGrid.h"
#include "GridCell.h"
#include "Grid.h"
#include <math.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// file: AStar.h
//
// summary:	Finds the shortest path between the start and goal nodes using the A* algorithm by defining a grid based on the position.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

class AStar {
public:
	/// <summary>	List of possible next cells int he path. </summary>
	std::vector<GridCell*> possibleNextCells;
	/// <summary>	Path found during the first calculation. </summary>
	std::vector<GridCell*> initialPath;
	/// <summary>	Path found during the latest calculation. </summary>
	std::vector<GridCell*> currentPath;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="_startNode">	The node of the spawnpoint. </param>
	/// <param name="_goalNode"> 	The node of the target object. </param>
	/// <param name="_obstacle">  	A list of places that have obstacles placed on them. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	AStar(scene::ISceneNode* _startNode, scene::ISceneNode* _goalNode, Grid* _grid);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~AStar();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Searches for the shortest path. </summary>
	///
	/// <remarks> Recursive method that checks neighbouring cells untill it reaches the goal. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void FindPath();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Reverse path. </summary>
	///
	/// <param name="_path">	The path to the goal. </param>
	///
	/// <returns>	returns the path to the goal in reverse order. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<GridCell*> ReversePath(std::vector<GridCell*> _path);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Next cell. </summary>
	///
	/// <returns>	Return the cell with the lowest heuristic according to A*. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	GridCell* NextCell();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Searches for the shortest path. </summary>
	///
	/// <remarks> Resets the pathfinding and calls FindPath(). </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool RecalculatePath(core::vector3df spawnedPosition);

	std::vector<GridCell*> GetSurroundingCells(core::vector3df position);
	/// <summary>	The start cell. </summary>
	GridCell* pStartCell;
	/// <summary>	The goal cell. </summary>
	GridCell* pGoalCell;
	/// <summary>	The targeted cell. </summary>
	GridCell* pTargetCell;
	Grid* grid;
	int cellsPassed;
	int maxCells = 700;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get the centre of a cell. </summary>
	///
	///
	/// <param name="position">	The selected position. </param>
	///
	/// <returns>	Returns the centre of the cell that is selected. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	core::vector3df GetCentre(core::vector3df position);
	GridCell* GetCell(core::vector3df position);
	void SetObstacle(bool filled, core::vector3df position);

	//bool isPathValid()
};
