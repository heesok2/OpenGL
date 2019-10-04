#include "stdafx.h"
#include "EntityVertex.h"


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
