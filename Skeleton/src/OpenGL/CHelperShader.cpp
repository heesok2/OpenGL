#include "CHelperShader.h"
#include <atltrace.h>

CHelperShader::CHelperShader()
	: m_uiProgram(0)
{
}

CHelperShader::~CHelperShader()
{
}

bool CHelperShader::GLBind()
{
	if (!m_uiProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found program\n");
		return false;
	}

	glUseProgram(m_uiProgram);
	return true;
}

bool CHelperShader::GLLoad(unsigned int eShaderType)
{
	if (!GLCreateProgram())
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to GLCreateProgram\n");
		return false;
	}

	auto hMod = GetModuleHandle(nullptr);
	switch (eShaderType)
	{
	case E_SHADER_GLFW:
		{
			if (!GLAttachShader(GL_VERTEX_SHADER, hMod, IDR_SHADER_GLFW_VERT) ||
				!GLAttachShader(GL_FRAGMENT_SHADER, hMod, IDR_SHADER_GLFW_FRAG))
			{
				ATLASSERT(false);
				ATLTRACE("[error] Failed to GLAttachShader\n");
				return false;
			}
		}
		break;
	default:
		{
			ATLASSERT(false);
			ATLTRACE("[error] unknown type\n");
			return false;
		}
		break;
	}

	if (!GLLinkShader())
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to GLLinkShader\n");
		return false;
	}

	return true;
}

void CHelperShader::GLUnbind()
{
	glUseProgram(0);
}

void CHelperShader::GLDelete()
{
	glDeleteProgram(m_uiProgram);
}

bool CHelperShader::GLCreateProgram()
{
	ATLTRACE("create program\n");

	if (m_uiProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] duplicate program\n");
		return false;
	}

	m_uiProgram = glCreateProgram();
	return m_uiProgram > 0;
}

bool CHelperShader::GLAttachShader(GLenum target, HMODULE hMod, const unsigned int uiResID)
{
	if (!m_uiProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found program\n");
		return false;
	}

	if (hMod == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found module\n");
		return false;
	}

	auto hRes = FindResource(hMod, MAKEINTRESOURCE(uiResID), "GLSL");
	if (hRes == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found resource\n");
		return false;
	}

	auto dwResSize = SizeofResource(hMod, hRes);
	auto hResData = LoadResource(hMod, hRes);
	if (dwResSize == 0 || hResData == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to load\n");
		return false;
	}

	GLchar* aSource = new GLchar[dwResSize + 1];
	auto aResData = reinterpret_cast<const GLchar*>(LockResource(hResData));
	std::copy(aResData, aResData + dwResSize, aSource);
	aSource[dwResSize] = '\0';

	if (!GLCreateShader(target, hMod, aSource))
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to GLCreateShader\n");

		return false;
	}

	delete[] aSource;
	UnlockResource(hResData);
	FreeResource(hResData);

	return true;
}

bool CHelperShader::GLCreateShader(GLenum target, HMODULE hMod, const GLchar * aSource)
{
	auto nShader = glCreateShader(target);
	if (!nShader)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to create shader\n");
		return false;
	}

	glShaderSource(nShader, 1, &aSource, nullptr);
	glCompileShader(nShader);

	GLint nCompile = 0;
	glGetShaderiv(nShader, GL_COMPILE_STATUS, &nCompile);
	if (!nCompile)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to compile shader\n");

		GLint nLogLength = 0;
		glGetShaderiv(nShader, GL_INFO_LOG_LENGTH, &nLogLength);
		if (nLogLength > 0)
		{
			GLchar* aLog = new GLchar[nLogLength];
			glGetShaderInfoLog(nShader, nLogLength, &nLogLength, aLog);
			ATLTRACE("[error] Shader Info Log : %s\n", aLog);
			delete[] aLog;
		}

		return false;
	}

	switch (target)
	{
	case GL_VERTEX_SHADER:
		{
			m_aShaderVertex.push_back(nShader);
		}
		break;
	case GL_FRAGMENT_SHADER:
		{
			m_aShaderFragment.push_back(nShader);
		}
		break;
	default:
		{
			ATLASSERT(false);
			ATLTRACE("[error] unknown type\n");
			return false;
		}
		break;
	}

	glAttachShader(m_uiProgram, nShader);

	return true;
}

bool CHelperShader::GLLinkShader()
{
	glLinkProgram(m_uiProgram);

	GLint nLinkStatus;
	glGetProgramiv(m_uiProgram, GL_LINK_STATUS, &nLinkStatus);
	if (!nLinkStatus)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to program Link\n");
		return false;
	}

	//GLDetachShader();
	GLDeleteShader();

	return true;
}

void CHelperShader::GLDetachShader()
{
	auto lambda_detach = [&](std::vector<GLint>& aShader)
	{
		for (auto itr : aShader)
			glDetachShader(m_uiProgram, itr);
	};

	lambda_detach(m_aShaderVertex);
	lambda_detach(m_aShaderFragment);
}

void CHelperShader::GLDeleteShader()
{
	auto lambda_clear = [&](std::vector<GLint>& aShader)
	{
		for (auto itr : aShader)
			glDeleteShader(itr);

		aShader.clear();
	};

	lambda_clear(m_aShaderVertex);
	lambda_clear(m_aShaderFragment);
}
