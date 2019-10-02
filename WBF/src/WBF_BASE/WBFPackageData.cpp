#include "stdafx.h"
#include "WBFPackageData.h"
#include "DocListener.h"
#include "ListenerDefine.h"

#include "..\WBF_LIB\WBFObserverDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFPackageData::CWBFPackageData(CWBFDocBase* pDoc)
	: m_pMyDoc(pDoc)
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
	//Notify(E_UPDATE_DB_CHANGED);

	CDocListener::DoNotifyMsg(m_pMyDoc, E_DOC_DB_UPDATE, 0);

	return TRUE;
}

BOOL CWBFPackageData::Rollback()
{
	return  FALSE;
}
