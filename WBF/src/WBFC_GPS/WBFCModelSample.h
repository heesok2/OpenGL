#pragma once

#include "..\WBF_BASE\WBFModelBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCModelSample : public CWBFModelBase
{
	DECLARE_MODEL(CWBFCModelSample);

public:
	CWBFCModelSample();
	virtual ~CWBFCModelSample();

public:
	virtual BOOL IsValidModel();

	virtual void GLInitialData();
	virtual void GLCreateVBO();
	virtual void GLBind();
	virtual void GLDraw();
	virtual void GLUnbind();
	virtual void GLDelete();

protected:

protected:
	UINT m_uiVAO; // Vertex Attribute Object
	UINT m_uiVBO; // Vertex Buffer Object
	UINT m_uiEBO; // Element Buffer Object

};

#include "HeaderPost.h"

