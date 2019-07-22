#pragma once

#include "GlfwIncludeHeader.h"
#include "ShaderDef.h"

class CShaderVBO
{
public:
	CShaderVBO();
	virtual ~CShaderVBO();

public:
	bool GLBind();
	void GLUnbind();
	bool GLLoadVBO(unsigned int eShaderType);

private:
	GLuint m_uiVAO;
	GLuint m_uiVBO;
	GLuint m_uiEBO;
	
};

