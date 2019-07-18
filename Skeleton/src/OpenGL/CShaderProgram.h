#pragma once

#include "GlfwIncludeHeader.h"
#include "resource.h"
#include <vector>
#include <Windows.h>

class CShaderProgram
{
public:
	CShaderProgram();
	virtual ~CShaderProgram();

public:
	bool GLCreate();
	void GLClearShader();
	void GLLoadShader(unsigned int eShaderType);

private:
	bool GLAttachShader(GLenum target, HMODULE hMod, const unsigned int uiResID);
	bool GLAttachShaderSource(GLenum target, HMODULE hMod, const GLchar* aSource);
	GLint GLCompileShaderSource(GLenum target, const GLchar* aSource);

private:
	GLint m_nProgram;
	std::vector<GLint> m_aShaderVertex;
	std::vector<GLint> m_aShaderFragment;
};

