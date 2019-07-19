#include "CShaderProgram.h"
#include <atltrace.h>

CShaderProgram::CShaderProgram()
	: m_nProgram(0)
{
}

CShaderProgram::~CShaderProgram()
{
}

bool CShaderProgram::GLBind()
{
	if (!m_nProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found program");
		return false;
	}

	glUseProgram(m_nProgram);
	return true;
}

void CShaderProgram::GLUnbind()
{
	glUseProgram(0);
}

bool CShaderProgram::GLLoadShader(unsigned int eShaderType)
{
	if (!GLCreateProgram())
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to GLCreateProgram");
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
				ATLTRACE("[error] Failed to GLAttachShader");
				return false;
			}
		}
		break;
	default:
		{
			ATLASSERT(false);
			ATLTRACE("[error] unknown type");
			return false;
		}
		break;
	}

	if (!GLLinkShader())
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to GLLinkShader");
		return false;
	}

	return true;
}

bool CShaderProgram::GLCreateProgram()
{
	ATLTRACE("create program");

	if (m_nProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] duplicate program");
		return false;
	}

	m_nProgram = glCreateProgram();
	return m_nProgram > 0;
}

bool CShaderProgram::GLAttachShader(GLenum target, HMODULE hMod, const unsigned int uiResID)
{
	if (!m_nProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found program");
		return false;
	}

	if (hMod == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found module");
		return false;
	}

	auto hRes = FindResource(hMod, MAKEINTRESOURCE(uiResID), "GLSL");
	if (hRes == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found resource");
		return false;
	}

	auto dwResSize = SizeofResource(hMod, hRes);
	auto hResData = LoadResource(hMod, hRes);
	if (dwResSize == 0 || hResData == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to load");
		return false;
	}

	GLchar* aSource = new GLchar[dwResSize + 1];
	auto aResData = reinterpret_cast<const GLchar*>(LockResource(hResData));
	std::copy(aResData, aResData + dwResSize, aSource);
	aSource[dwResSize] = '\0';

	if (!GLCreateShader(target, hMod, aSource))
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to GLCreateShader");

		return false;
	}

	delete[] aSource;
	UnlockResource(hResData);
	FreeResource(hResData);

	return true;
}

bool CShaderProgram::GLCreateShader(GLenum target, HMODULE hMod, const GLchar * aSource)
{
	auto nShader = glCreateShader(target);
	if (!nShader)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to create shader");
		return false;
	}

	glShaderSource(nShader, 1, &aSource, nullptr);
	glCompileShader(nShader);

	GLint nCompile = 0;
	glGetShaderiv(nShader, GL_COMPILE_STATUS, &nCompile);
	if (!nCompile)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to compile shader");

		GLint nLogLength = 0;
		glGetShaderiv(nShader, GL_INFO_LOG_LENGTH, &nLogLength);
		if (nLogLength > 0)
		{
			GLchar* aLog = new GLchar[nLogLength];
			glGetShaderInfoLog(nShader, nLogLength, &nLogLength, aLog);
			ATLTRACE("[error] Shader Info Log : %s", aLog);
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
			ATLTRACE("[error] unknown type");
			return false;
		}
		break;
	}

	glAttachShader(m_nProgram, nShader);

	return true;
}

bool CShaderProgram::GLLinkShader()
{
	glLinkProgram(m_nProgram);

	GLint nLinkStatus;
	glGetProgramiv(m_nProgram, GL_LINK_STATUS, &nLinkStatus);
	if (!nLinkStatus)
	{
		ATLASSERT(false);
		ATLTRACE("[error] Failed to program Link");
		return false;
	}

	GLDetachShader();
	GLDeleteShader();

	return true;
}

void CShaderProgram::GLDetachShader()
{
	auto lambda_detach = [&](std::vector<GLint>& aShader)
	{
		for (auto itr : aShader)
			glDetachShader(m_nProgram, itr);
	};

	lambda_detach(m_aShaderVertex);
	lambda_detach(m_aShaderFragment);
}

void CShaderProgram::GLDeleteShader()
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
