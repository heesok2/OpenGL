#include "stdafx.h"
#include "ModuleMesh.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleMesh::CModuleMesh(CPackage * pPackage)
	: CModuleData<CEntityMesh>(pPackage, E_TYPE_MESH)
{
}

CModuleMesh::~CModuleMesh()
{
}
