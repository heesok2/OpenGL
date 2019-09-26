#include "stdafx.h"
#include "ModuleGeom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleGeom::CModuleGeom(CWBFPackageData * pPackage)
	: CWBFModuleData<CEntityGeom>(pPackage, E_TYPE_GEOM)
{
}

CModuleGeom::~CModuleGeom()
{
}

void CModuleGeom::SetDefaultData()
{
	CEntityGeom tGeom;
	tGeom.dbKey = GetNewKey();

	
}
