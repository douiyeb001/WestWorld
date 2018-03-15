#pragma once
#include <math.h>

#define WORLD_SIZE 64

struct SearchGrid
{

public:
	int m_xcoord, m_zcoord;
	int m_id;
	SearchGrid *parent;
	float G;
	float H;

	SearchGrid() : parent(0) {}
	SearchGrid(int x, int z, SearchGrid *_parent = 0) : m_xcoord(x), m_zcoord(z),
		parent(_parent), m_id(z * WORLD_SIZE + x), G(0), H(0) {};

	float GetF() { return G + H; }
	float ManhattanDistance(SearchGrid *nodeEnd)
	{
		float x = (float)(fabs((float)this->m_xcoord - nodeEnd->m_xcoord));
		float z = (float)(fabs((float)this->m_zcoord - nodeEnd->m_zcoord));

		return x + z;
	}
};