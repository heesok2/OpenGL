#include "stdafx.h"
#include "EntityVertex.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityVertex::CEntityVertex() 
{
	dbKey = 0;

	vPos = glm::vec3(0);
	vNormal = glm::vec3(0);
	vTexcord = glm::vec2(0);
}

CEntityVertex::~CEntityVertex()
{
}

const DTYPE CEntityVertex::GetType() const
{
	return E_TYPE_VERTEX;
}

const DKEY CEntityVertex::GetKey() const
{
	return dbKey;
}