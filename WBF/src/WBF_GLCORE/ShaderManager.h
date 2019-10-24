#pragma once

#include "Shader.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CShaderManager
{
public:
	CShaderManager();
	virtual ~CShaderManager();

public:
	BOOL IsValidShader(UINT uiType);
	CShader& GetShader(UINT uiType);

	void GLShaderVersion();
	void GLCreateShader(UINT uiType);

protected:
	std::map<unsigned int, CShader> m_mBuildShader;

};

#include "HeaderPost.h"