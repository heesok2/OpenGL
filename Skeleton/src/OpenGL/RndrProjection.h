#pragma once

#include "IRndrBase.h"

class CRndrProjection :
	public IRndrBase
{
public:
	CRndrProjection();
	virtual ~CRndrProjection();

public:
	// IRndrBase을(를) 통해 상속됨
	virtual bool Run() override;

private:
	static void MyDisplayFunc();
	static void MyTimeFunc(int value);

private:
	static void DrawInit();
	static void DrawScene();
	static void DrawCoodinate();

private:
	static int g_menu_mode; // render mode
	
	static int g_width; // window size
	static int g_height; // window size
	static int g_volumn; // view volumn
	static int g_near;
	static int g_far;

	static int g_angle;

};