#pragma once

#include <irrlicht.h>
#include <vector3d.h>
#include <vector>
#include "SearchGrid.h"

class PathFinding
{
public:
	PathFinding();
	~PathFinding();


	void FindPath(irr::core::vector3df currentPosition, irr::core::vector3df targetPosition);
	irr::core::vector3df NextPathPosition();
	void ClearOpenList() { m_openList.clear(); }
	void ClearVisitedList() { m_visitedList.clear(); }
	void ClearPathGoal() { m_pathToGoal.clear(); }
	bool m_initializedStartGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(SearchGrid start, SearchGrid goal);
	void PathOpened(int x, int z, float newCost, SearchGrid *parent);
	SearchGrid *GetNextCell();
	void ContinuePath();

	SearchGrid *m_startCell;
	SearchGrid *m_goalCell;
	std::vector<SearchGrid*> m_openList;
	std::vector<SearchGrid*> m_visitedList;
	std::vector<irr::core::vector3df*> m_pathToGoal;
};

