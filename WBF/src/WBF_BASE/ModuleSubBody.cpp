#include "stdafx.h"
#include "ModuleSubBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleSubBody::CModuleSubBody(CWBFPackageData * pPackage)
	: CWBFModuleData<CEntitySubBody>(pPackage, E_TYPE_SUBBODY)
{
}

CModuleSubBody::~CModuleSubBody()
{
}

void CModuleSubBody::SetDefaultData()
{
}
