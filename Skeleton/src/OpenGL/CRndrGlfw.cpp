#include <iostream>
#include "CRndrGlfw.h"
#include "CHelperShader.h"
#include "CHelperVBO.h"

int g_width = 500;
int g_height = 500;

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
	CHelperShader shader;
	if (!shader.GLLoad(E_SHADER_GLFW))
	{
		std::cout << "Failed to initialize shader" << std::endl;
		glfwTerminate();
		return false;
	}

	// 5. initialize vbo
	CHelperVBO vbo;
	if (!vbo.GLLoad(E_SHADER_GLFW))
	{
		std::cout << "Failed to initialize shader vbo" << std::endl;
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, g_width, g_height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	// wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 6. loop
	while (!glfwWindowShouldClose(pWnd))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.GLBind();
		{
			vbo.GLBind();
			vbo.GLDraw();
			vbo.GLUnbind();
		}
		shader.GLUnbind();

		glfwSwapBuffers(pWnd);
		glfwPollEvents(); // check event
	}

	// 7. destroy resource
	vbo.GLDelete();
	shader.GLDelete();

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