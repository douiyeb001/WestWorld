#pragma once
#include <irrlicht.h>

using namespace irr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A health bar. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class HealthBar : public scene::ISceneNode
{

	/// <summary>	The box. </summary>
	core::aabbox3d<f32> Box;
	/// <summary>	The vertices[ 6]. </summary>
	video::S3DVertex Vertices[6];
	/// <summary>	The material. </summary>
	video::SMaterial Material;

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="parent">	[in,out] If non-null, the parent. </param>
	/// <param name="mgr">   	[in,out] If non-null, the manager. </param>
	/// <param name="id">	 	The identifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	HealthBar(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes the register scene node action. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void OnRegisterSceneNode();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Renders this object. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void render();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets bounding box. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <returns>	The bounding box. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets material count. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <returns>	The material count. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual u32 getMaterialCount() const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a material. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="i">	Zero-based index of the. </param>
	///
	/// <returns>	The material. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual video::SMaterial& getMaterial(u32 i);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets a health. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="health">	The health. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SetHealth(int health);
};

