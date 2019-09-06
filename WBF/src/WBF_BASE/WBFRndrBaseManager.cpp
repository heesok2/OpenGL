#include "stdafx.h"
#include "WBFRndrBaseManager.h"

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