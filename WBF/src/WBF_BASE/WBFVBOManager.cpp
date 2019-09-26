#include "stdafx.h"
#include "WBFVBOManager.h"

#include "WBFDocBase.h"
#include "WBFViewBase.h"
#include "WBFPackageData.h"
#include "WBFVBOData.h"

#include "..\WBF_LIB\WBFObserverDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFVBOManager::CWBFVBOManager(CWBFDocBase* pDoc)
	: m_pMyDoc(pDoc)
{

}

CWBFVBOManager::~CWBFVBOManager()
{
}

void CWBFVBOManager::UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
}

void CWBFVBOManager::OnInitial()
{
	//auto pPackage = m_pMyDoc->GetPackage();
	//pPackage->Attached(this);
}

void CWBFVBOManager::OnDestroy()
{
	//auto pPackage = m_pMyDoc->GetPackage();
	//pPackage->Dettached(this);
}