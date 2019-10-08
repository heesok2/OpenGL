#include "stdafx.h"
#include "DocBase.h"
#include "ViewBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDocBase::CDocBase()
{
}

CDocBase::~CDocBase()
{
}

CViewBase * CDocBase::GetActiveView()
{
	auto pos = GetFirstViewPosition();
	while (pos != nullptr)
	{
		auto pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CViewBase)))
			return static_cast<CViewBase*>(pView);
	}

	ASSERT(g_warning);
	return nullptr;
}