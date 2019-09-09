#pragma once

#include "WBFShader.h"
#include <map>

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFShaderManager
{
public:
	CWBFShaderManager();
	virtual ~CWBFShaderManager();

public:
	BOOL IsValidShader(UINT uiType);
	CWBFShader& GetShader(UINT uiType);

	void GLShaderVersion();
	void GLCreateShader(UINT uiType);

protected:
	std::map<unsigned int, CWBFShader> m_mBuildShader;

};
#include "HeaderPost.h"