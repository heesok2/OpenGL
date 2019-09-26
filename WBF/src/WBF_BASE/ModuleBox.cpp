#include "stdafx.h"
#include "ModuleBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleBox::CModuleBox(CWBFPackageData * pPackage)
	: CWBFModuleData<CEntityBox>(pPackage, E_TYPE_BOX)
{
}

CModuleBox::~CModuleBox()
{
}