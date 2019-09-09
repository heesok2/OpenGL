#include "stdafx.h"
#include "WBFRndrBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFRndrBase::CWBFRndrBase()
	: m_pRndrMgr(nullptr), m_pModelMgr(nullptr)
{

}

CWBFRndrBase::~CWBFRndrBase()
{

}