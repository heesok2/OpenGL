#include "stdafx.h"
#include "WBFModuleBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFModuleBase::CWBFModuleBase(CWBFPackageData * pPackage)
	: m_pPackage(pPackage)
{
}

CWBFModuleBase::~CWBFModuleBase()
{
}