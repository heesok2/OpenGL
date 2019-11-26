#include "stdafx.h"
#include "ModuleGround.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleGround::CModuleGround(CPackage * pPackage)
	: CModuleData<CEntityGround>(pPackage, E_TYPE_GROUND)
{
	m_dbDefaultKey = 1;
}

CModuleGround::~CModuleGround()
{
}

DITER CModuleGround::GetDefaultData()
{
	auto itrLight = Find(m_dbDefaultKey);
	if (!ITR_IS_VALID(itrLight))
		return NULL; //ASSERT(g_warning);

	return itrLight;
}

void CModuleGround::SetDefaultData()
{
	if (!Empty()) return;

	const float fRange = 4.f;

	CEntityGround Data;
	Data.dbKey = m_dbDefaultKey;
	Data.aPos[0] = glm::vec3(-fRange, -fRange, fRange);
	Data.aPos[1] = glm::vec3(fRange, -fRange, fRange);
	Data.aPos[2] = glm::vec3(fRange, -fRange, -fRange);
	Data.aPos[3] = glm::vec3(-fRange, -fRange, -fRange);

	InsertNU(Data);
}