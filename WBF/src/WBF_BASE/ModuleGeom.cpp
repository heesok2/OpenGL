#include "stdafx.h"
#include "ModuleGeom.h"

CModuleGeom::CModuleGeom()
	: CWBFModuleData<CEntityGeom>(E_TYPE_GEOM)
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
