#include "CHelperVBO.h"
#include <atltrace.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	: m_uiVAO(0), m_uiVBO(0), m_uiEBO(0)
{
	m_uiTex[0] = m_uiTex[1] = 0;
}

CHelperVBO::~CHelperVBO()
{
}

bool CHelperVBO::GLBind()
{
	if (!m_uiTex)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found texture\n");
		return false;
	}

	if (!m_uiVAO)
	{
		ATLASSERT(false);
		ATLTRACE("[error] not found vao\n");
		return false;
	}

	glm::mat4 trans(1.f);
	trans = glm::rotate(trans, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	GLint nProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &nProgram);
	glUniform1i(glGetUniformLocation(nProgram, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(nProgram, "ourTexture2"), 1);
	glUniformMatrix4fv(glGetUniformLocation(nProgram, "transform"), 1, false, glm::value_ptr(trans));

	glBindVertexArray(m_uiVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTex[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_uiTex[1]);	
	
	return true;
}

bool CHelperVBO::GLLoad(unsigned int eShaderType)
{
	switch (eShaderType)
	{
	case E_SHADER_GLFW:
		{
			stbi_set_flip_vertically_on_load(true);

			glGenTextures(2, m_uiTex);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_uiTex[0]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
			{
				// set the texture wrapping parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				// set texture filtering parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// load image, create texture and generate mipmaps
				int width, height, nrChannels;
				// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.

				char aPath[MAX_PATH+1] = { 0 };
				auto dwSize = GetModuleFileName(nullptr, aPath, MAX_PATH);
				std::string strPath = aPath;
				auto item = strPath.find_last_of("\\");
				if (item != -1)
				{
					std::string strDir = strPath.substr(0, item);
					strDir += "\\Image\\container.jpg";

					unsigned char *data = stbi_load(strDir.c_str(), &width, &height, &nrChannels, 0);
					if (data != nullptr)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
						glGenerateMipmap(GL_TEXTURE_2D);
					}
					else
					{
						// failed load imag
					}

					stbi_image_free(data);
				}
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_uiTex[1]);
			{
				// set the texture wrapping parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				// set texture filtering parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// load image, create texture and generate mipmaps
				int width, height, nrChannels;
				// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.

				char aPath[MAX_PATH + 1] = { 0 };
				auto dwSize = GetModuleFileName(nullptr, aPath, MAX_PATH);
				std::string strPath = aPath;
				auto item = strPath.find_last_of("\\");
				if (item != -1)
				{
					std::string strDir = strPath.substr(0, item);
					strDir += "\\Image\\awesomeface.png";

					unsigned char *data = stbi_load(strDir.c_str(), &width, &height, &nrChannels, 0);
					if (data != nullptr)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
						glGenerateMipmap(GL_TEXTURE_2D);
					}
					else
					{
						// failed load imag
					}

					stbi_image_free(data);
				}
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			glGenVertexArrays(1, &m_uiVAO);
			glGenBuffers(1, &m_uiVBO);
			glGenBuffers(1, &m_uiEBO);
			
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
			ATLTRACE("[error] unknown type\n");
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
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void CHelperVBO::GLDelete()
{
	glDeleteVertexArrays(1, &m_uiVAO);
	glDeleteTextures(2, m_uiTex);
}
