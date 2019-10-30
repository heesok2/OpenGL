#include "stdafx.h"
#include "Package.h"
#include "DocListener.h"
#include "ListenerDefine.h"

#include "..\WBF_LIB\WBFObserverDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPackage::CPackage(CDocument* pDoc)
	: m_pMyDoc(pDoc)
{
}


CPackage::~CPackage()
{
}

BOOL CPackage::Start()
{
	return TRUE;
}

BOOL CPackage::Commit()
{
	Notify(E_UPDATE_DB_CHANGED);

	CDocListener::DoNotifyMsg(m_pMyDoc, E_DOCUMENT_DB_UPDATE, 0);

	return TRUE;
}

BOOL CPackage::Rollback()
{
	return  FALSE;
}
