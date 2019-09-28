#include "stdafx.h"
#include "ModelAppManager.h"
#include "VBOGeom.h"

#include "..\WBF_LIB\WBFObserverDefine.h"
#include "..\WBF_BASE\WBFModelFactory.h"
#include "..\WBF_BASE\WBFModelData.h"
#include "..\WBF_BASE\WBFVBOManager.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFPackageData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModelAppManager::CModelAppManager(CWBFViewBase* pView)
	: CWBFModelDataManager(pView), m_pVBOMgr(nullptr)
{
}


CModelAppManager::~CModelAppManager()
{
}

void CModelAppManager::UpdateObserver(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case E_UPDATE_DB_CHANGED:
		{
			m_pVBOMgr->UpdateObserver(uiMsg, wParam, lParam);

			OnUpdateAll();
		}
		break;
	default:
		break;
	}
}

void CModelAppManager::OnInitial()
{
	CWBFModelDataManager::OnInitial();

	auto pPackage = m_pMyDoc->GetPackage();
	if (pPackage) pPackage->Attached(this);
	
	m_pVBOMgr = new CWBFVBOManager(m_pMyDoc);
	m_pVBOMgr->OnInitial();
}

void CModelAppManager::OnDestroy()
{
	auto pPackage = m_pMyDoc->GetPackage();
	if (pPackage) pPackage->Dettached(this);

	if (m_pVBOMgr != nullptr)
		m_pVBOMgr->OnDestroy();

	_SAFE_DELETE(m_pVBOMgr);

	CWBFModelDataManager::OnDestroy();
}

void CModelAppManager::OnUpdateAll()
{
	for (auto pObject : m_vObject)
		pObject->SetFlag(MODEL_UPDATE);
}

void CModelAppManager::OnUpdateOnly(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			pObject->SetFlag(MODEL_UPDATE);
	}
}

void CModelAppManager::GLInitialData()
{
	for (auto pObject : m_vObject)
	{
		auto uiFlag = pObject->GetFlag();
		if (uiFlag & MODEL_UPDATE)
		{
			pObject->GLInitialData();
			pObject->GLCreateVBO();
		}

		pObject->InitFlag();
	}
}