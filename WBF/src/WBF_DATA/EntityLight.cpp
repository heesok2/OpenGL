#include "stdafx.h"
#include "EntityLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityLight::CEntityLight()
{
	dbKey = 0;
	uiType = E_ENT_POINT;
	dbBodyKey = 0;
	vPos = glm::vec3(0);
}

CEntityLight::~CEntityLight()
{
}

void CEntityLight::SetDefaultData()
{
	dbKey = 0;
	uiType = E_ENT_POINT;
	dbBodyKey = 0;
	vPos = glm::vec3(0);
}