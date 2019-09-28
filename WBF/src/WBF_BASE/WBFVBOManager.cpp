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
	switch (uiMsg)
	{
	case E_UPDATE_DB_CHANGED:
		{
			for (auto pVBO : m_lstVBO)
			{
				pVBO->ProcessData(m_pMyDoc);
			}
		}
		break;
	default:
		break;
	}
}

void CWBFVBOManager::OnInitial()
{
	for (UINT uiType = 0; uiType < E_VBO_NUM; ++uiType)
	{
		auto pObject = (CWBFVBOData*)CWBFVBOFactory::GetInstance().CreateObject(uiType);
		if (pObject == nullptr) continue;

		m_lstVBO.push_back(pObject);
	}
}

void CWBFVBOManager::OnDestroy()
{
	for (auto pVBO : m_lstVBO)
	{
		_SAFE_DELETE(pVBO);
	}
}