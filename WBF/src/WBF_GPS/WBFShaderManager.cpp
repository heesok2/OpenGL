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
	//���� ����ũž ������ ��ȭ�Ǹ鼭 �׷��� �ڿ��� ������� ���� �Ҵ�޴� ����� �ٲ������ ���δ�.
	//�Ʒ��� ���� Shader Version�� ȣ������ ���� ��찡 ���ܼ� ����ó�� �߰�
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