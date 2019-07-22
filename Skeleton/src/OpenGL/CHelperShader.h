#pragma once

#include "GlfwIncludeHeader.h"
#include "ShaderDef.h"

#include <vector>
#include <Windows.h>

class CHelperShader
{
public:
	CHelperShader();
	virtual ~CHelperShader();

public:
	bool GLBind();
	bool GLLoad(unsigned int eShaderType);
	void GLUnbind();	
	void GLDelete();

private:
	bool GLCreateProgram();
	bool GLAttachShader(GLenum target, HMODULE hMod, const unsigned int uiResID);
	bool GLCreateShader(GLenum target, HMODULE hMod, const GLchar* aSource);
	bool GLLinkShader();
	void GLDetachShader();
	void GLDeleteShader();

private:
	GLuint m_uiProgram;
	std::vector<GLint> m_aShaderVertex;
	std::vector<GLint> m_aShaderFragment;
};