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

BOOL CWBFShaderManager::IsValidShader(UINT uiType)
{
	auto itr = m_mBuildShader.find(uiType);
	return itr != m_mBuildShader.end();
}

CWBFShader & CWBFShaderManager::GetShader(UINT uiType)
{
	auto itr = m_mBuildShader.find(uiType);
	if (itr == m_mBuildShader.end())
	{
		ASSERT(g_warning);
		m_mBuildShader[uiType] = CWBFShader();
	}

	return m_mBuildShader[uiType];
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
		shader.GLAttachShader(GL_VERTEX_SHADER, std::string("res\\GLSL\\Sample_vert.glsl"));
		shader.GLAttachShader(GL_FRAGMENT_SHADER, std::string("res\\GLSL\\Sample_frag.glsl"));
	}
	break;
	default:
		break;
	}

	shader.GLLinkShader();
	m_mBuildShader[uiType] = shader;
}