#pragma once

#include "..\WBF_GPS\WBFViewGL.h"

#include "HeaderPre.h"

class CWBFRndrBaseManager;
class __MY_EXT_CLASS__ CWBFViewBase : public CWBFViewGL
{
public:
	CWBFViewBase();
	virtual ~CWBFViewBase();

public:
	virtual CWBFRndrBaseManager* GetRenderManager() { ASSERT(g_warning);  return nullptr; }

private:
	DECLARE_MESSAGE_MAP();

};

#include "HeaderPost.h"