#pragma once

#include "GlfwIncludeHeader.h"
#include "IRndrBase.h"

class CRndrGlfw : public IRndrBase
{
public:
	CRndrGlfw();
	virtual ~CRndrGlfw();

public:
	virtual bool Run() override;

private:
	static void CallbackSizeFunc(GLFWwindow* pWnd, int width, int height);
	static void CallbackKeyFunc(GLFWwindow* pWnd, int key, int scancode, int action, int mods);
};