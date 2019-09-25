#include "stdafx.h"
#include "WBFPackageData.h"

#include "..\WBF_LIB\WBFObserverDefine.h"

CWBFPackageData::CWBFPackageData()
{
}


CWBFPackageData::~CWBFPackageData()
{
}

void CWBFPackageData::Start()
{

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
