#include "stdafx.h"
#include "EntitySubBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntitySubBody::CEntitySubBody()
{
	Init();
}


CEntitySubBody::~CEntitySubBody()
{
}

void CEntitySubBody::Init()
{
	dbKey = 0;

	uiSubType = 0;;
}
