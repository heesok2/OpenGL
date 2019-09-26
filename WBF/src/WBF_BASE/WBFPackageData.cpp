#include "stdafx.h"
#include "WBFPackageData.h"

#include "..\WBF_LIB\WBFObserverDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFPackageData::CWBFPackageData()
{
}


CWBFPackageData::~CWBFPackageData()
{
}

BOOL CWBFPackageData::Start()
{
	return TRUE;
}

BOOL CWBFPackageData::Commit()
{
	Notify(E_UPDATE_DB_CHANGED);
	return TRUE;
}

BOOL CWBFPackageData::Rollback()
{
	return  FALSE;
}
