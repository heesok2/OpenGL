#pragma once

#include "IRndrBase.h"

class CRndrAliasing : public IRndrBase
{
public:
	CRndrAliasing();
	virtual ~CRndrAliasing();

public:
	// IRndrBase을(를) 통해 상속됨
	virtual bool Run() override;

private:
	void DrawInit();
	static void DrawRedisplay();

private:
	static void MyDisplayFunc();
	static void MyMiniDisplayFunc();
	static void MyWorldDisplayFunc();
	static void MyKeyboardFunc(unsigned char ch, int x, int y);
	static void MyTimerFunc(int value);
	
private:
	static int g_menu_mode; // render mode

	static int g_win_x; // window position x
	static int g_win_y; // window position y
	static int g_width; // window size
	static int g_height; // window size
	static int g_volumn; // view volumn
	static int g_near;
	static int g_far;

	static int g_angle;

};

