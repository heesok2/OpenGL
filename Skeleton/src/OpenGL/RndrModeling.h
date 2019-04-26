#pragma once

#include "IRndrBase.h"

class CRndrModeling :
	public IRndrBase
{
public:
	CRndrModeling();
	virtual ~CRndrModeling();

public:
	virtual bool Run() override;

private:
	static void MyDisplayFunc();
	static void MyKeyboardFunc(unsigned char key, int x, int y);

private:
	static int g_menu_mode; // render mode

	static int g_width; // window size
	static int g_height; // window size
	static int g_volumn; // view volumn
	static float  g_view_near;
	static float  g_view_far;

	static int g_hour;
	static int g_day;
	static int g_month;
};