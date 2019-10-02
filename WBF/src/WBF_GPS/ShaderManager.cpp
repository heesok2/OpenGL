#include "stdafx.h"
#include "resource.h"
#include "ShaderManager.h"
#include "ShaderDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShaderManager::CShaderManager()
{
}


CShaderManager::~CShaderManager()
{
}

BOOL CShaderManager::IsValidShader(UINT uiType)
{
	auto itr = m_mBuildShader.find(uiType);
	return itr != m_mBuildShader.end();
}

CShader & CShaderManager::GetShader(UINT uiType)
{
	auto itr = m_mBuildShader.find(uiType);
	if (itr == m_mBuildShader.end())
	{
		ASSERT(g_warning);
		m_mBuildShader[uiType] = CShader();
	}

	return m_mBuildShader[uiType];
}

void CShaderManager::GLShaderVersion()
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

void CShaderManager::GLCreateShader(UINT uiType)
{
	CShader shader;
	shader.GLCreateProgram();

	switch (uiType)
	{
	case E_SHADER_SAMPLE:
		{
			shader.GLAttachShader(GL_VERTEX_SHADER, IDR_SHADER_SAMPLE_VERT);
			shader.GLAttachShader(GL_FRAGMENT_SHADER, IDR_SHADER_SAMPLE_FRAG);
		}
		break;
	case E_SHADER_LIGHT:
		{
			shader.GLAttachShader(GL_VERTEX_SHADER, IDR_SHADER_LIGHT_VERT);
			shader.GLAttachShader(GL_FRAGMENT_SHADER, IDR_SHADER_LIGHT_FRAG);
		}
		break;
	default:
		break;
	}

	shader.GLLinkShader();
	m_mBuildShader[uiType] = shader;
}