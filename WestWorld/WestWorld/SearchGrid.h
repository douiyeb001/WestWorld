#pragma once
#include <math.h>

#define WORLD_SIZE 512

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A search grid. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

struct SearchGrid
{

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the zcoord. </summary>
	///
	/// <value>	The m zcoord. </value>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	int m_xcoord, m_zcoord;
	/// <summary>	The identifier. </summary>
	int m_id;
	/// <summary>	The parent. </summary>
	SearchGrid *parent;
	/// <summary>	A float to process. </summary>
	float G;
	/// <summary>	The height. </summary>
	float H;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	SearchGrid() : parent(0) {}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="x">	  	The x coordinate. </param>
	/// <param name="z">	  	The z coordinate. </param>
	/// <param name="_parent">	[in,out] (Optional) If non-null, the parent. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	SearchGrid(int x, int z, SearchGrid *_parent = 0) : m_xcoord(x), m_zcoord(z),
		parent(_parent), m_id(z * WORLD_SIZE + x), G(0), H(0) {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the f. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <returns>	The f. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	float GetF() { return G + H; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Manhattan distance. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="nodeEnd">	[in,out] If non-null, the node end. </param>
	///
	/// <returns>	A float. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	float ManhattanDistance(SearchGrid *nodeEnd)
	{
		/// <summary>	The x coordinate. </summary>
		float x = (float)(fabs((float)this->m_xcoord - nodeEnd->m_xcoord));
		/// <summary>	The z coordinate. </summary>
		float z = (float)(fabs((float)this->m_zcoord - nodeEnd->m_zcoord));

		return x + z;
	}
};