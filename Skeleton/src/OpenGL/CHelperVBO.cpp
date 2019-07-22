#include "CHelperVBO.h"
#include <atltrace.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLfloat g_aVertices[] =
{
	// 0
	-0.5f, -0.5f, 0.f,	// vertex
	1.f, 0.f, 0.f,		// color
	0.f, 0.f,			// texture

	// 1
	0.5f, -0.5f, 0.f,	// vertex 
	0.f, 1.f, 0.f,		// color
	1.f, 0.f,			// texture

	// 2
	0.5f, 0.5f, 0.f,	// vertex
	0.f, 0.f, 1.f,		// color
	1.f, 1.f,			// texture

	// 3
	-0.5f, 0.5f, 0.f,	// vertex
	0.f, 1.f, 0.f,		// color
	0.f, 1.f,			// texture
};

GLuint g_aIndexs[] =
{
	0, 1, 2,
	0, 2, 3,
};

CHelperVBO::CHelperVBO()
	: m_uiVAO(0), m_uiVBO(0), m_uiEBO(0), m_uiTex(0)
{
}

CHelperVBO::~CHelperVBO()
{
}

bool CHelperVBO::GLBind()
{
	if (!m_uiVAO)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found vao");
		return false;
	}

	glBindVertexArray(m_uiVAO);

	return true;
}

bool CHelperVBO::GLLoad(unsigned int eShaderType)
{
	switch (eShaderType)
	{
	case E_SHADER_GLFW:
		{
			glGenVertexArrays(1, &m_uiVAO);
			glGenBuffers(1, &m_uiVBO);
			glGenBuffers(1, &m_uiEBO);

			glGenTextures(1, &m_uiTex);
			glBindTexture(GL_TEXTURE_2D, m_uiTex);
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}

			int width, height, nrChannels;
			auto data = stbi_load("Image/container.jpg", &width, &height, &nrChannels, 0);


			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);





			glBindVertexArray(m_uiVAO);
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_aVertices), g_aVertices, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_aIndexs), g_aIndexs, GL_STATIC_DRAW);

				// vertex, stride 6
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GLfloat)));
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GLfloat)));
				glEnableVertexAttribArray(2);

			}
			glBindVertexArray(0);

			glDeleteBuffers(1, &m_uiVBO);
			glDeleteBuffers(1, &m_uiEBO);
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

	return true;
}

void CHelperVBO::GLDraw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);// (3 * sizeof(GLuint)));
}

void CHelperVBO::GLUnbind()
{
	glBindVertexArray(0);
}

void CHelperVBO::GLDelete()
{
	glDeleteVertexArrays(1, &m_uiVAO);
}
