#pragma once

#include "GlfwIncludeHeader.h"
#include "ShaderDef.h"

class CHelperVBO
{
public:
	CHelperVBO();
	virtual ~CHelperVBO();

public:
	bool GLBind();
	bool GLLoad(unsigned int eShaderType);
	void GLDraw();
	void GLUnbind();
	void GLDelete();

private:
	GLuint m_uiVAO;
	GLuint m_uiVBO;
	GLuint m_uiEBO;
	GLuint m_uiTex;

};

