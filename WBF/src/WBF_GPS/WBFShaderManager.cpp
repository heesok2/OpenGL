#include "stdafx.h"
#include "WBFShaderManager.h"
#include "..\WBF_BASE\WBFGraphicDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFShaderManager::CWBFShaderManager()
{
}


CWBFShaderManager::~CWBFShaderManager()
{
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

void CWBFShaderManager::GLCreateShader(UINT uiType)
{
	CWBFShader shader;
	shader.GLCreateProgram();

	switch (uiType)
	{
	case gps::E_GPS_SAMPLE:
		{
			shader.GLAttachShader(GL_VERTEX_SHADER, _T("res\\GLSL\\Sample_frag.glsl"));
			shader.GLAttachShader(GL_FRAGMENT_SHADER, _T("res\\GLSL\\Sample_vert.glsl"));
		}
		break;
	default:
		break;
	}

	shader.GLLinkShader();

	m_mBuildShader[uiType] = shader;
}