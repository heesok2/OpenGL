#pragma once

#include "..\WBF_BASE\WBFModelBase.h"
#include "..\WBF_GPS\WBFGPSOption.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFCModelSample : public CWBFModelBase
{
	DECLARE_MODEL(CWBFCModelSample);

public:
	CWBFCModelSample();
	virtual ~CWBFCModelSample();

public:
	virtual CWBFOption* GetOption() { return &m_Option; }
	virtual BOOL IsValidModel() { return m_uiVAO > 0; }

	virtual void GLInitialData();
	virtual void GLCreateVBO();
	virtual void GLAttachData();
	virtual void GLBind();
	virtual void GLDraw();
	virtual void GLUnbind();
	virtual void GLDelete();
	
protected:
	CWBFGPSOption m_Option;

	UINT m_uiVAO; // Vertex Attribute Object
	UINT m_uiVBO; // Vertex Buffer Object
	UINT m_uiEBO; // Element Buffer Object

	UINT m_uiTex;

};

#include "HeaderPost.h"

