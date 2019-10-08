#include "stdafx.h"
#include "EntityVertex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityVertex::CEntityVertex() 
{
	Init();
}

CEntityVertex::~CEntityVertex()
{
}

void CEntityVertex::Init()
{
	dbKey = 0;

	vPos = glm::vec3(0);
	vNormal = glm::vec3(0);
	vTexcord = glm::vec2(0);
}
