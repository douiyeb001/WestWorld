#include "PathFinding.h"

#include <irrlicht.h>
#include <vector3d.h>
#include <vector>
#include "SearchGrid.h"
#include "Opponent.h" 

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

PathFinding::PathFinding()
{
	/// <summary>	. </summary>
	m_initializedStartGoal = false;
	/// <summary>	. </summary>
	m_foundGoal = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

PathFinding::~PathFinding()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Searches for the first path. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="currentPosition">	The current position. </param>
/// <param name="targetPosition"> 	Target position. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PathFinding::FindPath(irr::core::vector3df currentPosition, irr::core::vector3df targetPosition)
{
	if (!m_initializedStartGoal)
	{
		for (int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for (int i = 0; i < m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for (int i = 0; i < m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		//initialize start
		/// <summary>	The start. </summary>
		SearchGrid start;
		/// <summary>	. </summary>
		start.m_xcoord = currentPosition.X;
		/// <summary>	. </summary>
		start.m_zcoord = currentPosition.Z;

		//initialize goal
		/// <summary>	Target for the. </summary>
		SearchGrid target;
		/// <summary>	. </summary>
		target.m_xcoord = targetPosition.X;
		/// <summary>	. </summary>
		target.m_zcoord = targetPosition.Z;

		SetStartAndGoal(start, target);
		m_initializedStartGoal = true;
	}

	if (m_initializedStartGoal)
	{
		ContinuePath();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Sets start and goal. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="start">	The start. </param>
/// <param name="goal"> 	The goal. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PathFinding::SetStartAndGoal(SearchGrid start, SearchGrid goal)
{
	/// <summary>	. </summary>
	m_startCell = new SearchGrid(start.m_xcoord, start.m_zcoord, NULL);
	/// <summary>	. </summary>
	m_goalCell = new SearchGrid(goal.m_xcoord, goal.m_zcoord, &goal);

	/// <summary>	. </summary>
	m_startCell->G = 0;
	/// <summary>	. </summary>
	m_startCell->H = m_startCell->ManhattanDistance(m_goalCell);
	/// <summary>	. </summary>
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the next cell. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <returns>	Null if it fails, else the next cell. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

SearchGrid* PathFinding::GetNextCell()
{
	/// <summary>	The best f. </summary>
	float bestF = 999999.0f;
	/// <summary>	Zero-based index of the cel. </summary>
	int celIndex = -1;
	/// <summary>	The next cell. </summary>
	SearchGrid* nextCell = NULL;

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			celIndex = i;
		}
	}

	if (celIndex >= 0)
	{
		nextCell = m_openList[celIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + celIndex);
	}

	return nextCell;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Path opened. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="x">	  	The x coordinate. </param>
/// <param name="z">	  	The z coordinate. </param>
/// <param name="newCost">	The new cost. </param>
/// <param name="parent"> 	[in,out] If non-null, the parent. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PathFinding::PathOpened(int x, int z, float newCost, SearchGrid *parent)
{
	/*if(CELL_BLOCKED)
	{
		return;
	}*/

	/// <summary>	The identifier. </summary>
	int id = z * WORLD_SIZE + x;
	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	SearchGrid* newChild = new SearchGrid(x, z, parent);
	/// <summary>	The new cost. </summary>
	newChild->G = newCost;
	/// <summary>	. </summary>
	newChild->H = parent->ManhattanDistance(m_goalCell);

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;

			if(m_openList[i]->GetF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else
			{
				delete newChild;
				return;
			}
		}
	}

	m_openList.push_back(newChild);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Continue path. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PathFinding::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	/// <summary>	The current cell. </summary>
	SearchGrid* currentCell = GetNextCell();

	/// <summary>	The first identifier. </summary>
	int id1 = currentCell->m_id;
	/// <summary>	The second identifier. </summary>
	int id2 = m_goalCell->m_id;

	if (currentCell->m_id == m_goalCell->m_id)
	{
		m_goalCell->parent = currentCell->parent;

		/// <summary>	Full pathname of the get file. </summary>
		SearchGrid* getPath;

		for (getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
		{
			m_pathToGoal.push_back(new irr::core::vector3df(getPath->m_xcoord, 0, getPath->m_zcoord));
		}

		m_foundGoal = true;
		return;
	}
	else
	{
		//rightCell
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
		//leftCell
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
		//Up
		PathOpened(currentCell->m_xcoord, currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
		//Down
		PathOpened(currentCell->m_xcoord, currentCell->m_zcoord - 1, currentCell->G + 1, currentCell);
		//Left-Up Diagonal
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
		//Right-Up Diagonal
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
		//Left-Down Diagonal
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord - 1, currentCell->G + 1, currentCell);
		//Right-Down Diagonal
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord - 1, currentCell->G + 1, currentCell);

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + i);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	ContinuePath();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Next path position. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="enemy">	[in,out] If non-null, the enemy. </param>
///
/// <returns>	An irr::core::vector3df. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

irr::core::vector3df PathFinding::NextPathPosition(Opponent* enemy)
{
	if (m_pathToGoal.size() == 0)
		return enemy->enemy->getAbsolutePosition();
	/// <summary>	Zero-based index of the. </summary>
	int index = 1;

	irr::core::vector3df nextPos;
	/// <summary>	The next X position towards the goal. </summary>
	nextPos.X = m_pathToGoal[m_pathToGoal.size() - index]->X;
	/// <summary>	The next Z postion towards the goal. </summary>
	nextPos.Z = m_pathToGoal[m_pathToGoal.size() - index]->Z;

	/// <summary>	poss is the position of the enemy in our case it qould be opponent. </summary>
	irr::core::vector3df distance = nextPos - enemy->enemy->getAbsolutePosition();

	//if (index < m_pathToGoal.size())
	//{
		//if (distance.getLength() < 1)
		//{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		//}
	//}

	return nextPos;
}