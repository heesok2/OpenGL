#include "stdafx.h"
#include "RndrManager.h"
#include "RndrData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRndrManager::CRndrManager(CViewBase* pView)
	: m_pView(pView)
{
}

CRndrManager::~CRndrManager()
{
}

CRndrData * CRndrManager::GetRender(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			return pObject;
	}

	ASSERT(g_warning);
	return nullptr;
}
