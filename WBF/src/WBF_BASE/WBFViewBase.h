#pragma once

#include "..\WBF_GPS\WBFViewGL.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFViewBase : public CWBFViewGL
{
public:
	CWBFViewBase();
	virtual ~CWBFViewBase();

private:
	DECLARE_MESSAGE_MAP();

};

#include "HeaderPost.h"