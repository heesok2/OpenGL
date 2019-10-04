#include "stdafx.h"
#include "EntityLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityLight::CEntityLight()
{
	Init();
}

CEntityLight::~CEntityLight()
{
}

void CEntityLight::Init()
{
	dbKey = 0;

	uiType = E_ENT_DIRECTIONAL;
	vPos = glm::vec3(0);
}