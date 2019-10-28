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
	BOOL GLSetInt(const char* aName, int nData);
	BOOL GLSetBoolean(const char* aName, bool bData);
	BOOL GLSetfloat(const char* aName, float fData);
	BOOL GLSetDouble(const char* aName, double dData);

protected:
	unsigned int m_nProg;
	std::vector<UINT> m_vShader;
};

#include "HeaderPost.h"
