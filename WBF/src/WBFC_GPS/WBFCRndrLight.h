#pragma once

#include "..\WBF_BASE\WBFRndrBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCRndrLight : public CWBFRndrBase
{
	DECLARE_RENDERER(CWBFCRndrLight);

public:
	CWBFCRndrLight();
	virtual ~CWBFCRndrLight();

public:
	// CWBFRndrBase��(��) ���� ��ӵ�
	virtual void GLDraw() override;
};

#include "HeaderPost.h"
