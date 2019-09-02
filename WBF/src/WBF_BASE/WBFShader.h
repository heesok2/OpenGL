#pragma once

#include <vector>
#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFShader
{
public:
	CWBFShader();
	virtual ~CWBFShader();

public:
	void GLCreateProgram();
	void GLAttachShader(unsigned int nShaderType, CString strPath);
	void GLLinkShader();

protected:
	unsigned int m_nProg;
	std::vector<unsigned int> m_vShader;
};

#include "HeaderPost.h"
