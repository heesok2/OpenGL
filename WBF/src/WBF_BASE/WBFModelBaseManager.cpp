#include "stdafx.h"
#include "WBFModelBaseManager.h"
#include "WBFModelBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFModelBaseManager::CWBFModelBaseManager(CWBFDocBase* pDoc)
	: m_pDoc(pDoc)
{
}


CWBFModelBaseManager::~CWBFModelBaseManager()
{
}

CWBFModelBase * CWBFModelBaseManager::GetModel(UINT uiType)
{
	for (auto pObject : m_vObject)
	{
		if (pObject->GetType() == uiType)
			return pObject;
	}

	ASSERT(g_warning);
	return nullptr;
}
