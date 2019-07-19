#include "CShaderProgram.h"
#include "ShaderDef.h"

#include <atltrace.h>

CShaderProgram::CShaderProgram()
	: m_nProgram(0)
{
}

CShaderProgram::~CShaderProgram()
{
}

GLint CShaderProgram::GLCreate()
{
	ATLTRACE("program 积己");

	if (m_nProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[warning] program 吝汗 积己");
		return m_nProgram;
	}

	m_nProgram = glCreateProgram();
	return m_nProgram;
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

void CShaderProgram::GLLoadShader(unsigned int eShaderType)
{
	auto hMod = GetModuleHandle(nullptr);
	switch (eShaderType)
	{
	case E_SHADER_GLFW:
		{
			if (!GLAttachShader(GL_VERTEX_SHADER, hMod, IDR_SHADER_GLFW_VERT) ||
				!GLAttachShader(GL_FRAGMENT_SHADER, hMod, IDR_SHADER_GLFW_FRAG))
			{
				ATLASSERT(false);
				ATLTRACE("[warning] failed GLAttachShader");

				return;
			}
		}
		break;
	default:
		{
			ATLASSERT(false);
			ATLTRACE("[warning] unknown type");

			return;
		}
		break;
	}

	if (!GLLinkShader())
	{
		ATLASSERT(false);
		ATLTRACE("[warning] failed GLLinkShader");
	}
}

bool CShaderProgram::GLLinkShader()
{
	glLinkProgram(m_nProgram);

	GLint nLinkStatus;
	glGetProgramiv(m_nProgram, GL_LINK_STATUS, &nLinkStatus);
	if (!nLinkStatus)
	{
		ATLASSERT(false);
		ATLTRACE("[error] failed program Link");

		return false;
	}

	GLDetachShader();
	GLDeleteShader();

	return true;
}

bool CShaderProgram::GLAttachShader(GLenum target, HMODULE hMod, const unsigned int uiResID)
{
	if (!m_nProgram)
	{
		ATLASSERT(false);
		ATLTRACE("[error] do not created shader program");

		return false;
	}

	if (hMod == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] do not created module");

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
	if (hResData == nullptr)
	{
		ATLASSERT(false);
		ATLTRACE("[error] failed load");

		return false;
	}

	auto aResData = reinterpret_cast<const GLchar*>(LockResource(hResData));

	GLchar* aSource = new GLchar[dwResSize + 1];
	std::copy(aResData, aResData + dwResSize, aSource);
	aSource[dwResSize] = '\0';

	if (!GLAttachShaderSource(target, hMod, aSource))
	{
		ATLASSERT(false);
		ATLTRACE("[error] failed GLAttachShaderSource");

		return false;
	}

	delete[] aSource;
	UnlockResource(hResData);
	FreeResource(hResData);

	return true;
}

bool CShaderProgram::GLAttachShaderSource(GLenum target, HMODULE hMod, const GLchar * aSource)
{
	auto nShader = GLCompileShaderSource(target, aSource);
	if (!nShader)
	{
		ATLASSERT(false);
		ATLTRACE("[error] failed GLCompileShaderSource");

		return false;
	}

	glAttachShader(m_nProgram, nShader);
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
			ATLTRACE("[warning] unknown type");
		}
		break;
	}

	return true;
}

GLint CShaderProgram::GLCompileShaderSource(GLenum target, const GLchar * aSource)
{
	auto nShader = glCreateShader(target);
	if (!nShader)
	{
		ATLASSERT(false);
		ATLTRACE("[error] failed create shader");

		return 0;
	}

	glShaderSource(nShader, 1, &aSource, nullptr);
	glCompileShader(nShader);

	GLint nCompile = 0;
	glGetShaderiv(nShader, GL_COMPILE_STATUS, &nCompile);
	if (!nCompile)
	{
		ATLASSERT(false);
		ATLTRACE("[error] failed compile shader");

		GLint nLogLength = 0;
		glGetShaderiv(nShader, GL_INFO_LOG_LENGTH, &nLogLength);
		if (nLogLength > 0)
		{
			GLchar* aLog = new GLchar[nLogLength];
			glGetShaderInfoLog(nShader, nLogLength, &nLogLength, aLog);
			ATLTRACE("[error] Shader Info Log : %s", aLog);
			delete[] aLog;
		}

		return 0;
	}

	return nShader;
}
