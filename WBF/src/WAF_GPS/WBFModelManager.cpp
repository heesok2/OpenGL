#include "stdafx.h"
#include "WBFModelManager.h"

#include "..\WBF_LIB\WBFObserverDefine.h"
#include "..\WBF_LIB\ListenerDefine.h"
#include "..\WBF_LIB\Package.h"
#include "..\WBF_BASE\ViewBase.h"
#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ModelFactory.h"
#include "..\WBF_BASE\ModelData.h"
#include "..\WBF_BASE\WBFVBOManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFModelManager::CWBFModelManager(CViewBase* pView)
	: CModelManager(pView), m_pVBOMgr(nullptr)
{
}


CWBFModelManager::~CWBFModelManager()
{
}

void CWBFModelManager::OnNotifyMsg(CDocument * pDoc, WPARAM wParam, LPARAM)
{
	if (m_pMyDoc != pDoc) return;

	switch (wParam)
	{
	case E_DOCUMENT_DB_UPDATE:
		{
			m_pView->BeginwglCurrent();
			{
				ReleaseModel();

				m_pVBOMgr->RebuildVBO();

				BuildModel();
			}
			m_pView->EndwglCurrent();
		}
		break;
	default:
		break;
	}

}

void CWBFModelManager::ReleaseModel()
{
	for (auto pModel : m_vObject)
		pModel->Release();
}

void CWBFModelManager::BuildModel()
{
	for (auto pModel : m_vObject)
		pModel->Build();
}

void CWBFModelManager::OnInitial()
{
	CModelManager::OnInitial();

	m_pVBOMgr = new CVBOManager(m_pMyDoc);
	m_pVBOMgr->OnInitial();
}

void CWBFModelManager::OnDestroy()
{
	if (m_pVBOMgr != nullptr)
		m_pVBOMgr->OnDestroy();

	_SAFE_DELETE(m_pVBOMgr);

	CModelManager::OnDestroy();
}

void CWBFModelManager::OnUpdateAll()
{
	/*for (auto pObject : m_vObject)
		pObject->SetFlag(MODEL_UPDATE);*/
}

void CWBFModelManager::OnUpdateOnly(UINT )
{
	//for (auto pObject : m_vObject)
	//{
	//	if (pObject->GetType() == uiType)
	//		pObject->SetFlag(MODEL_UPDATE);
	//}
}

void CWBFModelManager::GLInitialData()
{
	//for (auto pObject : m_vObject)
	//{
	//	auto uiFlag = pObject->GetFlag();
	//	if (uiFlag & MODEL_UPDATE)
	//	{
	//		pObject->GLInitialData();
	//		pObject->GLCreateVBO();
	//	}

	//	pObject->InitFlag();
	//}
}