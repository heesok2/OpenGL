#pragma once

#include "..\WBF_BASE\WBFRndrData.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRndrLight : public CWBFRndrData
{
	DECLARE_RENDERER(CRndrLight);

public:
	CRndrLight();
	virtual ~CRndrLight();

public:
	// CWBFRndrBase��(��) ���� ��ӵ�
	virtual void GLDraw() override;
};

#include "HeaderPost.h"
