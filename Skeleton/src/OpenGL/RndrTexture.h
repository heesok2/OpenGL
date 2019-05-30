#pragma once

#include "IRndrBase.h"
class CRndrTexture : public IRndrBase
{
public:
	CRndrTexture();
	virtual ~CRndrTexture();

public: // virtual function
	// IRndrBase을(를) 통해 상속됨
	virtual bool Run() override;

private: // member function
	static void DrawInit();
	static void DrawLighting();

private: // callback function
	static void MyDisplayFunc();
	static void MyReshapeFunc(int width, int height);

private:
	static int g_x, g_y;
	static int g_width, g_height;
	static int g_volumn, g_near, g_far;

	static int g_win_command;
	static int g_angle;
};

