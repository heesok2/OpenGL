#pragma once

#include "IRndrBase.h"
class CRndrLighting : public IRndrBase
{
public:
	CRndrLighting();
	virtual ~CRndrLighting();

public: // virtual function
	// IRndrBase을(를) 통해 상속됨
	virtual bool Run() override;

private: // static member function
	static void DrawInit();
	static void DrawLighting();

private: // callback function
	static void MyDisplayFunc();
	static void MyReshapeFunc(int width, int height);
	static void MyTimerFunc(int val);

private:
	static int g_win_x, g_win_y;
	static int g_width, g_height;
	static int g_volumn, g_near, g_far;

	static int g_win_command;
	static int g_angle;

};

