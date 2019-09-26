#include "stdafx.h"
#include "WBFRndrDataManager.h"
#include "WBFRndrData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFRndrDataManager::CWBFRndrDataManager(CWBFViewBase* pView)
	: m_pView(pView)
{
}

CWBFRndrDataManager::~CWBFRndrDataManager()
{
}

CWBFRndrData * CWBFRndrDataManager::GetRender(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			return pObject;
	}

	ASSERT(g_warning);
	return nullptr;
}
