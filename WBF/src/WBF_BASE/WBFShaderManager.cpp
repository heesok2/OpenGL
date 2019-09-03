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

void CWBFShaderManager::GLShaderVersion()
{
	char* strSLVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	//원격 데스크탑 보안이 강화되면서 그래픽 자원을 윈도우로 부터 할당받는 방법이 바뀐것으로 보인다.
	//아래와 같이 Shader Version을 호출하지 못한 경우가 생겨서 예외처리 추가
	if (strSLVersion)
	{
		
	}
	else
	{
	}
}
