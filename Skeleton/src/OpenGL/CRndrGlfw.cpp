#include <iostream>
#include "CRndrGlfw.h"

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
	auto pWnd = glfwCreateWindow(500, 500, "LearnOpenGL", nullptr, nullptr);
	if (pWnd == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(pWnd);

	// 3. initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	// 4. viewport
	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(pWnd, CallbackSizeFunc);
	glfwSetKeyCallback(pWnd, CallbackKeyFunc);

	// 5. message loop
	while (!glfwWindowShouldClose(pWnd))
	{
		GLInit();




		glfwSwapBuffers(pWnd); 
		glfwPollEvents(); // check event
	}

	// 6. destroy resource
	glfwTerminate();

	return true;
}

void CRndrGlfw::CallbackSizeFunc(GLFWwindow * pWnd, int width, int height)
{
	glViewport(0, 0, width, height);
}

void CRndrGlfw::CallbackKeyFunc(GLFWwindow * pWnd, int key, int scancode, int action, int mods)
{
}

void CRndrGlfw::GLInit()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
