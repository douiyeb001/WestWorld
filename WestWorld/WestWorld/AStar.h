#pragma once
#include <irrlicht.h>
#include <vector3d.h>
#include <vector>
#include <map>
#include "SearchGrid.h"
#include "GridCell.h"
#include <math.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

class AStar
{
public:
	/// <summary>	Dictionary of cells. </summary>
	std::map<int, GridCell> CellDictionary;
	/// <summary>	The possible next cells. </summary>
	std::vector<GridCell*> possibleNextCells;
	/// <summary>	Full pathname of the final file. </summary>
	std::vector<GridCell*> finalPath;
	std::vector<GridCell*> initialPath;
	std::vector<GridCell*> currentPath;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="startNode_">	[in,out] If non-null, the start node. </param>
	/// <param name="goalNode_"> 	[in,out] If non-null, the goal node. </param>
	/// <param name="Obstacle">  	True to obstacle. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, bool Obstacle[(World_Size / Cell_Size)*(World_Size / Cell_Size)]);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	AStar(scene::ISceneNode* startNode_, scene::ISceneNode* goalNode_, std::vector<bool> Obstacle);
	~AStar();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Searches for the first path. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void findPath();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Reverse path. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name=">">	[in,out] If non-null, the > </param>
	///
	/// <returns>	Null if it fails, else a std::vector&lt;GridCell*&gt; </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<GridCell*> ReversePath(std::vector<GridCell*>);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Next cell. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <returns>	Null if it fails, else a pointer to a GridCell. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector<GridCell*> ReversePath(std::vector<GridCell*> path);
	void RecalculatePath(core::vector3df spawnedPosition);
	GridCell* nextCell();
	/// <summary>	The goal cell. </summary>
	GridCell* startCell;
	GridCell* goalCell;

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

	GridCell* targetCell;
	int coordinatesToID(int x, int z);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Next path position. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="pos">  	The position. </param>
	/// <param name="speed">	The speed. </param>
	///
	/// <returns>	A core::vector3df. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	core::vector3df NextPathPosition(irr::core::vector3df pos, float speed);
	core::vector3df getCentre(core::vector3df position);
	//core::vector3df NextPathPosition(irr::core::vector3df pos, float speed);
};

