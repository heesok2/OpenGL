#include "stdafx.h"
#include "WBFRndrBaseManager.h"
#include "WBFRndrBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFRndrBaseManager::CWBFRndrBaseManager(CWBFViewBase* pView)
	: m_pView(pView)
{
}

CWBFRndrBaseManager::~CWBFRndrBaseManager()
{
}

CWBFRndrBase * CWBFRndrBaseManager::GetRender(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			return pObject;
	}

	ASSERT(g_warning);
	return nullptr;
}
