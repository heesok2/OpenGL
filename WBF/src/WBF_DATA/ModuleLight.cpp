#include "stdafx.h"
#include "ModuleLight.h"
#include "ModuleBody.h"

#include "..\WBF_LIB\Package.h"

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

	auto pModuleBody = static_cast<CModuleBody*>(m_pPackage->GetModule(E_TYPE_BODY));
	auto itr = pModuleBody->Find(1);

	CEntityLight Data;
	Data.dbKey = GetNewKey();
	Data.uiType = E_ENT_POINT;
	Data.itrBody = itr;
	Data.vPos = glm::vec3(1.2f, 1.0f, 2.0f);

	InsertNU(Data);
}