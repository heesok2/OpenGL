#include "stdafx.h"
#include "WBFRndrManager.h"

#include "..\WBF_BASE\DocBase.h"
#include "..\WBF_BASE\ViewBase.h"
#include "..\WBF_BASE\RndrFactory.h"
#include "..\WBF_BASE\RndrData.h"
#include "..\WBF_GLCORE\ShaderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFRndrManager::CWBFRndrManager(CViewBase* pView)
	: CRndrManager(pView)
{
}

CWBFRndrManager::~CWBFRndrManager()
{
}

void CWBFRndrManager::OnInitial()
{
	m_pShaderManager = new CShaderManager();

	auto pModelMgr = m_pView->GetModelManager();

	for (UINT uiType = E_RNDR_SAMPLE; uiType < E_RNDR_NUM; ++uiType)
	{
		auto pObject = (CRndrData*)CRndrFactory::GetInstance().CreateObject(uiType);
		if (pObject == nullptr) continue;
		
		pObject->SetHelper(this, pModelMgr);
		pObject->OnInitialData();

		m_vObject.push_back(pObject);
	}
}

void CWBFRndrManager::OnDestroy()
{
	for (auto pObject : m_vObject)
	{
		_SAFE_DELETE(pObject);
	}

	m_vObject.clear();

	_SAFE_DELETE(m_pShaderManager);
}

void CWBFRndrManager::GLDrawScene()
{
	for (auto pObject : m_vObject)
		pObject->GLDraw();
}