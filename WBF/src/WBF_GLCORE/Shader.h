#pragma once

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CShader
{
public:
	CShader();
	virtual ~CShader();

public:
	void GLCreateProgram();
	void GLAttachShader(UINT nShaderType, UINT uiResID);
	void GLLinkShader();

	void GLBind();
	void GLUnbind();
	void GLSetInt(CString strName, int nData);
	void GLSetBoolean(CString strName, bool bData);
	void GLSetfloat(CString strName, float fData);
	void GLSetDouble(CString strName, double dData);

protected:
	unsigned int m_nProg;
	std::vector<UINT> m_vShader;
};

#include "HeaderPost.h"
