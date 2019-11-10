#include "stdafx.h"
#include "EntityGround.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityGround::CEntityGround()
{
	dbKey = 0;
	aPos[0] = aPos[1] = aPos[2] = aPos[3] = glm::vec3(0.f);
}

CEntityGround::~CEntityGround()
{
}

const DTYPE CEntityGround::GetType() const
{
	return E_TYPE_GROUND;
}

const DKEY CEntityGround::GetKey() const
{
	return dbKey;
}
