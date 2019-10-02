#include "stdafx.h"
#include "WBFVBOManager.h"

#include "WBFDocBase.h"
#include "WBFViewBase.h"
#include "WBFPackageData.h"
#include "WBFVBOData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CVBOManager::CVBOManager(CWBFDocBase* pDoc)
	: m_pMyDoc(pDoc)
{

}

CVBOManager::~CVBOManager()
{
}

BOOL CVBOManager::Exist(UINT eType)
{
	for (auto pVBO : m_lstVBO)
	{
		if (pVBO->GetType() == eType)
			return TRUE;
	}

	return FALSE;
}

CVBOData* CVBOManager::Lookup(UINT eType)
{
	for (auto pVBO : m_lstVBO)
	{
		if (pVBO->GetType() == eType)
			return pVBO;
	}

	ASSERT(g_warning);
	return nullptr;
}

void CVBOManager::RebuildVBO()
{
	for (auto pVBO : m_lstVBO)
	{
		pVBO->Release();
		pVBO->Build(m_pMyDoc);
	}
}

void CVBOManager::OnInitial()
{
	for (UINT uiType = 0; uiType < E_VBO_NUM; ++uiType)
	{
		auto pObject = (CVBOData*)CWBFVBOFactory::GetInstance().CreateObject(uiType);
		if (pObject == nullptr) continue;

		m_lstVBO.push_back(pObject);
	}
}

void CVBOManager::OnDestroy()
{
	for (auto pVBO : m_lstVBO)
	{
		_SAFE_DELETE(pVBO);
	}
}