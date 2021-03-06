#pragma once

#ifndef DEFINE_TYPE
#define DEFINE_TYPE

enum E_TYPE_DATA
{
	E_TYPE_UNKNOWN = 0

	// Geometry
	, E_TYPE_VERTEX
	, E_TYPE_SUBBODY
	, E_TYPE_BODY

	// Mesh
	, E_TYPE_TEXTURE
	, E_TYPE_NODE
	, E_TYPE_ELEMENT
	, E_TYPE_MESH

	// Custom
	, E_TYPE_LIGHT
	, E_TYPE_GROUND
	, E_TYPE_BOX
	
	, E_TYPE_NUM
};

#endif // !DEFINE_TYPE
