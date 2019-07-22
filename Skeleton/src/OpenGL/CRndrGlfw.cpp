#include <iostream>
#include "CRndrGlfw.h"
#include "CShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int g_width = 500;
int g_height = 500;

GLfloat aVertices[] =
{
	-0.5f, -0.5f, 0.f, //0 
	1.f, 0.f, 0.f, //

	0.5f, -0.5f, 0.f, //2
	0.f, 1.f, 0.f, //

	0.5f, 0.5f, 0.f, //4
	0.f, 0.f, 1.f, //

	-0.5f, 0.5f, 0.f, //6
	0.f, 1.f, 0.f, //		
};

GLuint aIndexs[] =
{
	0, 1, 2,
	0, 2, 3,
};

CRndrGlfw::CRndrGlfw()
{
}

CRndrGlfw::~CRndrGlfw()
{
}

bool CRndrGlfw::Run()
{
	// 1. glfw window option 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2. glfw create window
	auto pWnd = glfwCreateWindow(g_width, g_height, "LearnOpenGL", nullptr, nullptr);
	if (pWnd == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(pWnd);
	glfwSetFramebufferSizeCallback(pWnd, CallbackSizeFunc);
	glfwSetKeyCallback(pWnd, CallbackKeyFunc);

	// 3. initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	// 4. initialize shader 
	CShaderProgram shader;
	if (!shader.GLLoadShader(E_SHADER_GLFW))
	{
		std::cout << "Failed to initialize shader" << std::endl;
		glfwTerminate();
		return false;
	}

	// 5. VAO(Vertex Attribute Object: VBO, EBO »ç¿ë)
	GLuint uiVAO, uiVBO, uiEBO;
	glGenVertexArrays(1, &uiVAO);
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiEBO);

	glBindVertexArray(uiVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(aIndexs), aIndexs, GL_STATIC_DRAW);

		// vertex, stride 6
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);

	glViewport(0, 0, g_width, g_height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	// wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 6. loop
	while (!glfwWindowShouldClose(pWnd))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.GLBind();
		glBindVertexArray(uiVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);// (3 * sizeof(GLuint)));
		glBindVertexArray(0);
		shader.GLUnbind();

		glfwSwapBuffers(pWnd);
		glfwPollEvents(); // check event
	}

	// 7. destroy resource
	glDeleteVertexArrays(1, &uiVAO);
	glDeleteBuffers(1, &uiVBO);
	glDeleteBuffers(1, &uiEBO);

	glfwTerminate();
	
	return true;
}

void CRndrGlfw::CallbackSizeFunc(GLFWwindow * pWnd, int width, int height)
{
	g_width = width;
	g_height = height;

	glViewport(0, 0, g_width, g_height);
}

void CRndrGlfw::CallbackKeyFunc(GLFWwindow * pWnd, int key, int scancode, int action, int mods)
{
	// Unknown
}