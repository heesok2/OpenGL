#pragma once

#include "..\WBF_BASE\ModelData.h"
#include "..\WBF_GPS\WBFGPSOption.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModelSample : public CModelData
{
	DECLARE_MODEL(CModelSample);

public:
	CModelSample();
	virtual ~CModelSample();

public:
	virtual UINT GetType() override { return E_MODEL_SAMPLE; }

	virtual opt::IWBFOption* GetOption() { return &m_Option; }
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
	BOOL m_bOnlyOne;

	UINT m_uiVAO; // Vertex Attribute Object
	UINT m_uiVBO; // Vertex Buffer Object
	UINT m_uiEBO; // Element Buffer Object

	UINT m_uiTexJPG;
	UINT m_uiTexPNG;
	CString m_cstrPNG;
	CString m_cstrJPG;


	// CWBFModelData을(를) 통해 상속됨
	virtual void Release() override;

	virtual void Build() override;
	virtual void Draw(CShader*) {};

};

#include "HeaderPost.h"

