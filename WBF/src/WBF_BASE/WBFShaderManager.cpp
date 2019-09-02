#include "stdafx.h"
#include "WBFShaderManager.h"

CWBFShaderManager::CWBFShaderManager()
{
}


CWBFShaderManager::~CWBFShaderManager()
{
}

void CWBFShaderManager::GLCreateShader(E_SHADER_TYPE eType)
{
	CWBFShader sh;
	sh.GLCreateProgram();

	switch (eType)
	{
	case CWBFShaderManager::E_SHADER_SAMPLE:
		{
			sh.GLAttachShader(GL_VERTEX_SHADER, _T("res\\GLSL\\Sample_frag.glsl"));
			sh.GLAttachShader(GL_FRAGMENT_SHADER, _T("res\\GLSL\\Sample_vert.glsl"));
		}
		break;
	default:
		break;
	}

	sh.GLLinkShader();

	m_mBuildShader[eType] = sh;
}
