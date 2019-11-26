#include "stdafx.h"
#include "ModuleElement.h"
#include "EntityDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleElement::CModuleElement(CPackage * pPackage)
	: CModuleData<CEntityElement>(pPackage, E_TYPE_ELEMENT)
{
}

CModuleElement::~CModuleElement()
{
}
