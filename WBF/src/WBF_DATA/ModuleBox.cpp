#include "stdafx.h"
#include "ModuleBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleBox::CModuleBox(CPackage * pPackage)
	: CModuleData<CEntityBox>(pPackage, E_TYPE_BOX)
{
}

CModuleBox::~CModuleBox()
{
}

void CModuleBox::SetDefaultData()
{
	if (!Empty()) return;

}
