#include "stdafx.h"
#include "EntityMesh.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityMesh::CEntityMesh()
{
}

CEntityMesh::~CEntityMesh()
{
}

const DTYPE CEntityMesh::GetType() const
{
	return E_TYPE_MESH;
}

const DKEY CEntityMesh::GetKey() const
{
	return dbKey;
}
