#include "stdafx.h"
#include "WBFModelDataManager.h"
#include "WBFModelData.h"
#include "WBFVBOManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFModelDataManager::CWBFModelDataManager(CWBFDocBase* pDoc)
	: m_pMyDoc(pDoc), m_pVBOMgr(nullptr)
{
}


CWBFModelDataManager::~CWBFModelDataManager()
{
}

void CWBFModelDataManager::OnInitial()
{
	m_pVBOMgr = new CWBFVBOManager(m_pMyDoc);
	m_pVBOMgr->OnInitial();
}

void CWBFModelDataManager::OnDestroy()
{
	if (m_pVBOMgr != nullptr)
		m_pVBOMgr->OnDestroy();

	_SAFE_DELETE(m_pVBOMgr);
}

CWBFModelData * CWBFModelDataManager::GetModel(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			return pObject;
	}

	//ASSERT(g_warning);
	return nullptr;
}

