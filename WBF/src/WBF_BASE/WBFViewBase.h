#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFViewBase : public CView
{
protected:
	CWBFViewBase();
	virtual ~CWBFViewBase();

public:
	// CView��(��) ���� ��ӵ�
	virtual void OnDraw(CDC * pDC) override;

private:
	DECLARE_MESSAGE_MAP();

};

#include "HeaderPost.h"