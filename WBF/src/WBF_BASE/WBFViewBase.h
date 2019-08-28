#pragma once

#include "WBFViewGL.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFViewBase : public CWBFViewGL
{
protected:
	CWBFViewBase();
	virtual ~CWBFViewBase();

private:
	DECLARE_MESSAGE_MAP();

};

#include "HeaderPost.h"