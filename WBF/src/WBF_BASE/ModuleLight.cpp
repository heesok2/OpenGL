#include "stdafx.h"
#include "ModuleLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleLight::CModuleLight(CPackage * pPackage)
	: CModuleData<CEntityLight>(pPackage, E_TYPE_LIGHT)
{
}

CModuleLight::~CModuleLight()
{
}

void CModuleLight::SetDefaultData()
{
	if (!Empty()) return;

	CEntityLight Data;
	Data.dbKey = GetNewKey();
	Data.uiType = E_ENT_POINT;
	Data.vPos = glm::vec3(1.2f, 1.0f, 2.0f);

	Insert(Data);
}