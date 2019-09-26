#include "stdafx.h"
#include "ModuleBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleBody::CModuleBody(CWBFPackageData * pPackage)
	: CWBFModuleData<CEntityBody>(pPackage, E_TYPE_BODY)
{
}

CModuleBody::~CModuleBody()
{
}

void CModuleBody::SetDefaultData()
{
}
