#include "stdafx.h"
#include "ModuleVertex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleVertex::CModuleVertex(CWBFPackageData * pPackage)
	: CWBFModuleData<CEntityVertex>(pPackage, E_TYPE_VERTEX)
{
}

CModuleVertex::~CModuleVertex()
{
}

void CModuleVertex::SetDefaultData()
{
}
