#include "stdafx.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShader::CShader()
	: m_nProg(0)
{
}

CShader::~CShader()
{
}

void CShader::GLCreateProgram()
{
	m_nProg = glCreateProgram();
}

void CShader::GLAttachShader(UINT nShaderType, UINT uiResID)
{
	auto lambda_source = [](UINT uiRes, std::string& strSource)
	{
		auto hHandle = GetModuleHandle(_T("WBF_GPS.dll"));
		auto hRes = FindResource(hHandle, MAKEINTRESOURCE(uiRes), _T("GLSL"));
		if (hRes == nullptr)
			return FALSE;

		auto dwResSize = SizeofResource(hHandle, hRes);
		auto hResData = LoadResource(hHandle, hRes);
		if (dwResSize == 0 || hResData == nullptr)
			return FALSE;

		GLchar* aCode = new GLchar[dwResSize + 1];
		auto aResData = reinterpret_cast<const GLchar*>(LockResource(hResData));
		std::copy(aResData, aResData + dwResSize, aCode);
		aCode[dwResSize] = '\0';

		strSource = aCode;

		delete[] aCode;
		UnlockResource(hResData);
		FreeResource(hResData);

		return TRUE;
	};

	auto lambda_code = [](std::string csFilePath, std::string& code)
	{
		std::ifstream ifs;
		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			std::stringstream rb;

			ifs.open(csFilePath);
			rb << ifs.rdbuf();
			ifs.close();

			code = rb.str();
		}
		catch (const std::exception&)
		{
			// unknown
			return FALSE;
		}

		return TRUE;
	};

	auto lambda_status = [](unsigned int id, unsigned int type)
	{
		int nCompile = 0;
		glGetShaderiv(id, type, &nCompile);
		if (!nCompile)
		{
			int nLogLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &nLogLength);

			if (nLogLength > 0)
			{
				auto aLog = new char[nLogLength];
				glGetShaderInfoLog(id, nLogLength, &nLogLength, aLog);
				TRACE(aLog);
				delete[] aLog;
			}

			return FALSE;
		}

		return TRUE;
	};
	
	std::string strSource;
	lambda_source(uiResID, strSource);

	unsigned int nShader = glCreateShader(nShaderType);

	auto pSource = strSource.c_str();
	glShaderSource(nShader, 1, &pSource, NULL);
	glCompileShader(nShader);
	if (!lambda_status(nShader, GL_COMPILE_STATUS))
		return;

	glAttachShader(m_nProg, nShader);
	m_vShader.push_back(nShader);
}

void CShader::GLLinkShader()
{
	auto lambda_status = [](unsigned int id, unsigned int type)
	{
		int nStatus = 0;
		glGetProgramiv(id, type, &nStatus);
		if (!nStatus)
		{
			int nLogLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &nLogLength);

			if (nLogLength > 0)
			{
				auto aLog = new char[nLogLength];
				glGetProgramInfoLog(id, nLogLength, &nLogLength, aLog);
				TRACE(aLog);
				delete[] aLog;
			}

			return FALSE;
		}

		return TRUE;
	};
	
	glLinkProgram(m_nProg);
	if (!lambda_status(m_nProg, GL_LINK_STATUS))
	{
		// unknown
	}

	for (auto sh : m_vShader)
		glDeleteShader(sh);
}

void CShader::GLBind()
{
	glUseProgram(m_nProg);
}

void CShader::GLUnbind()
{
	glUseProgram(0);
}
