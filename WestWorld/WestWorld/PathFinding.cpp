#include "PathFinding.h"

#include <irrlicht.h>
#include <vector3d.h>
#include <vector>
#include "SearchGrid.h"

PathFinding::PathFinding()
{
	m_initializedStartGoal = false;
	m_foundGoal = false;
}


PathFinding::~PathFinding()
{
}

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
		SearchGrid start;
		start.m_xcoord = currentPosition.X;
		start.m_zcoord = currentPosition.Z;

		//initialize goal
		SearchGrid target;
		target.m_xcoord = targetPosition.X;
		target.m_zcoord = targetPosition.Z;

		SetStartAndGoal(start, target);
		m_initializedStartGoal = true;
	}

	if (m_initializedStartGoal)
	{
		ContinuePath();
	}
}

void PathFinding::SetStartAndGoal(SearchGrid start, SearchGrid goal)
{
	m_startCell = new SearchGrid(start.m_xcoord, start.m_zcoord, NULL);
	m_goalCell = new SearchGrid(goal.m_xcoord, goal.m_zcoord, &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManhattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

SearchGrid* PathFinding::GetNextCell()
{
	float bestF = 999999.0f;
	int celIndex = -1;
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

void PathFinding::PathOpened(int x, int z, float newCost, SearchGrid *parent)
{
	/*if(CELL_BLOCKED)
	{
		return;
	}*/

	int id = z * WORLD_SIZE + x;
	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	SearchGrid* newChild = new SearchGrid(x, z, parent);
	newChild->G = newCost;
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

void PathFinding::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	SearchGrid* currentCell = GetNextCell();

	if (currentCell->m_id == m_goalCell->m_id)
	{
		m_goalCell->parent = currentCell->parent;

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
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord + 1, currentCell->G + 1.414f, currentCell);
		//Right-Up Diagonal
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord + 1, currentCell->G + 1.414f, currentCell);
		//Left-Down Diagonal
		PathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord - 1, currentCell->G + 1.414f, currentCell);
		//Right-Down Diagonal
		PathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord - 1, currentCell->G + 1.414f, currentCell);

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + i);
			}
		}
	}
}

irr::core::vector3df PathFinding::NextPathPosition()
{
	int index = 1;

	irr::core::vector3df nextPos;
	nextPos.X = m_pathToGoal[m_pathToGoal.size() - index]->X;
	nextPos.Z = m_pathToGoal[m_pathToGoal.size() - index]->Z;

	irr::core::vector3df distance = nextPos - ai.pos; //poss is the position of the enemy in our case it qould be opponent

	if (index < m_pathToGoal.size())
	{
		if (distance.getLength() < ai.radius)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}

	return nextPos;
}