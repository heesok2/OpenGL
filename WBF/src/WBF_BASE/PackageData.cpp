#include "stdafx.h"
#include "PackageData.h"
#include "DocListener.h"
#include "ListenerDefine.h"

#include "..\WBF_LIB\WBFObserverDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPackageData::CPackageData(CWBFDocBase* pDoc)
	: m_pMyDoc(pDoc)
{
}


CPackageData::~CPackageData()
{
}

BOOL CPackageData::Start()
{
	return TRUE;
}

BOOL CPackageData::Commit()
{
	//Notify(E_UPDATE_DB_CHANGED);

	CDocListener::DoNotifyMsg(m_pMyDoc, E_DOC_DB_UPDATE, 0);

	return TRUE;
}

BOOL CPackageData::Rollback()
{
	return  FALSE;
}
