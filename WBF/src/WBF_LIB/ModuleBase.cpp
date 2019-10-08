#include "stdafx.h"
#include "ModuleBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleBase::CModuleBase(CPackage * pPackage)
	: m_uiFlag(FLAG_MODULE_UNKNOWN), m_pPackage(pPackage)
{
}

CModuleBase::~CModuleBase()
{
}