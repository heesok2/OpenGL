#pragma once

#include "GlfwIncludeHeader.h"
#include "ShaderDef.h"

#include <vector>
#include <Windows.h>

class CShaderProgram
{
public:
	CShaderProgram();
	virtual ~CShaderProgram();

public:
	bool GLBind();
	void GLUnbind();
	bool GLLoadShader(unsigned int eShaderType);	

private:
	bool GLCreateProgram();
	bool GLAttachShader(GLenum target, HMODULE hMod, const unsigned int uiResID);
	bool GLCreateShader(GLenum target, HMODULE hMod, const GLchar* aSource);
	bool GLLinkShader();
	void GLDetachShader();
	void GLDeleteShader();

private:
	GLint m_nProgram;
	std::vector<GLint> m_aShaderVertex;
	std::vector<GLint> m_aShaderFragment;
};