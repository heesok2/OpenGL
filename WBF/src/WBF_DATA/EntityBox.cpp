#include "stdafx.h"
#include "EntityBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityBox::CEntityBox()
{
	dbKey = 0;
	dbBodyKey = 0;
	vPos = glm::vec3(0);
}

CEntityBox::~CEntityBox()
{
}