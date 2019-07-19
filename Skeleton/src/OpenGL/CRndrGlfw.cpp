#include <iostream>
#include "CRndrGlfw.h"
#include "CShaderProgram.h"

int g_width = 500;
int g_height = 500;

GLfloat aVertices[] =
{
	-0.5f, -0.5f, 0.f,
	0.5f, -0.5f, 0.f,
	0.f, 0.5f, 0.f
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

	// 5. VBO(Vertex Buffer Object)
	GLuint uiVBO, uiVBA;
	glGenBuffers(1, &uiVBO);
	glGenVertexArrays(1, &uiVBA);

	// first vertex array bind, next vertex buffer bind
	glBindVertexArray(uiVBA);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), nullptr);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glViewport(0, 0, g_width, g_height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);

	// 6. loop
	while (!glfwWindowShouldClose(pWnd))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.GLBind();
		glBindVertexArray(uiVBA);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		shader.GLUnbind();

		glfwSwapBuffers(pWnd);
		glfwPollEvents(); // check event
	}

	// 7. destroy resource
	glDeleteVertexArrays(1, &uiVBA);
	glDeleteBuffers(1, &uiVBO);

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