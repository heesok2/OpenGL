#include "stdafx.h"
#include "WBFModelBaseManager.h"
#include "WBFModelBase.h"

#include "WBFDocBase.h"
#include "WBFPackageData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFModelBaseManager::CWBFModelBaseManager(CWBFDocBase* pDoc)
	: m_pMyDoc(pDoc)
{
}


CWBFModelBaseManager::~CWBFModelBaseManager()
{
}

void CWBFModelBaseManager::UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	// Unknown
}

void CWBFModelBaseManager::OnInitial()
{
	m_pMyDoc->GetDataPackage()->Attached(this);
}

void CWBFModelBaseManager::OnDestroy()
{
	m_pMyDoc->GetDataPackage()->Dettached(this);
}

CWBFModelBase * CWBFModelBaseManager::GetModel(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			return pObject;
	}

	ASSERT(g_warning);
	return nullptr;
}

