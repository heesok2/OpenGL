#include "stdafx.h"
#include "RndrAppManager.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\WBFRndrFactory.h"
#include "..\WBF_BASE\WBFRndrData.h"
#include "..\WBF_GPS\WBFShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRndrAppManager::CRndrAppManager(CWBFViewBase* pView)
	: CWBFRndrDataManager(pView)
{
}

CRndrAppManager::~CRndrAppManager()
{
}

void CRndrAppManager::OnInitial()
{
	m_pShaderManager = new CWBFShaderManager();

	auto pModelMgr = m_pView->GetModelManager();

	for (UINT uiType = gps::E_GPS_SAMPLE; uiType < gps::E_GPS_NUM; ++uiType)
	{
		auto pObject = CWBFRndrFactory::GetInstance().CreateObject(uiType);
		if (pObject == nullptr) continue;
		
		pObject->SetHelper(this, pModelMgr);
		pObject->OnInitialData();

		m_vObject.push_back(pObject);
	}
}

void CRndrAppManager::OnDestroy()
{
	for (auto pObject : m_vObject)
	{
		_SAFE_DELETE(pObject);
	}

	m_vObject.clear();

	_SAFE_DELETE(m_pShaderManager);
}

void CRndrAppManager::GLDrawScene()
{
	for (auto pObject : m_vObject)
		pObject->GLDraw();
}