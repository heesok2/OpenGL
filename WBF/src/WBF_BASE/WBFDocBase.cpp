#include "stdafx.h"
#include "WBFDocBase.h"
#include "WBFViewBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFDocBase::CWBFDocBase()
	: m_pPackage(nullptr)
{
}

CWBFDocBase::~CWBFDocBase()
{
}

CWBFViewBase * CWBFDocBase::GetActiveView()
{
	auto pos = GetFirstViewPosition();
	while (pos != nullptr)
	{
		auto pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CWBFViewBase)))
			return static_cast<CWBFViewBase*>(pView);
	}

	ASSERT(g_warning);
	return nullptr;
}