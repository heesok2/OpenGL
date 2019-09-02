#pragma once

#include "WBFShader.h"
#include <map>

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFShaderManager
{
public:
	enum E_SHADER_TYPE
	{
		E_SHADER_UNKNOWN = 0,
		E_SHADER_SAMPLE,

		E_SHADER_NUM
	};

public:
	CWBFShaderManager();
	virtual ~CWBFShaderManager();

public:
	void GLCreateShader(E_SHADER_TYPE eType);

protected:
	std::map<unsigned int, CWBFShader> m_mBuildShader;

};
#include "HeaderPost.h"

