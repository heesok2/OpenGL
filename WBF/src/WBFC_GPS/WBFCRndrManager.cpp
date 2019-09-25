#include "stdafx.h"
#include "WBFCRndrManager.h"

#include "..\WBF_BASE\WBFDocBase.h"
#include "..\WBF_BASE\WBFViewBase.h"
#include "..\WBF_BASE\WBFRndrFactory.h"
#include "..\WBF_BASE\WBFRndrBase.h"
#include "..\WBF_GPS\WBFShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFCRndrManager::CWBFCRndrManager(CWBFViewBase* pView)
	: CWBFRndrBaseManager(pView)
{
	m_pShaderMgr = new CWBFShaderManager();
}

CWBFCRndrManager::~CWBFCRndrManager()
{
}

void CWBFCRndrManager::OnInitial()
{
	auto pDocBase = (CWBFDocBase*)m_pView->GetDocument();
	auto pModelMgr = pDocBase->GetModelManager();

	for (UINT uiType = gps::E_GPS_SAMPLE; uiType < gps::E_GPS_NUM; ++uiType)
	{
		auto pObject = CWBFRndrFactory::GetInstance().CreateObject(uiType);
		if (pObject == nullptr) continue;
		
		pObject->SetHelper(this, pModelMgr);
		pObject->OnInitialData();

		m_vObject.push_back(pObject);
	}
}

void CWBFCRndrManager::OnDestroy()
{
	for (auto pObject : m_vObject)
	{
		_SAFE_DELETE(pObject);
	}

	m_vObject.clear();

	_SAFE_DELETE(m_pShaderMgr);
}

void CWBFCRndrManager::GLDrawScene()
{
	for (auto pObject : m_vObject)
		pObject->GLDraw();
}