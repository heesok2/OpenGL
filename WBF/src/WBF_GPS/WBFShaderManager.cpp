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

void CWBFShaderManager::GLCreateShader(UINT eType)
{
	CWBFShader sh;
	sh.GLCreateProgram();

	switch (eType)
	{
	case gps::E_GPS_SAMPLE:
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
	//���� ����ũž ������ ��ȭ�Ǹ鼭 �׷��� �ڿ��� ������� ���� �Ҵ�޴� ����� �ٲ������ ���δ�.
	//�Ʒ��� ���� Shader Version�� ȣ������ ���� ��찡 ���ܼ� ����ó�� �߰�
	if (strSLVersion)
	{
		
	}
	else
	{
	}
}
