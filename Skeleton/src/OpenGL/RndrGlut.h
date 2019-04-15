#pragma once

#include "IRndrBase.h"

class CRndrGlut : public IRndrBase
{
public:
	CRndrGlut();
	virtual ~CRndrGlut();

public:
	virtual bool Run() override;

private:
	static void MyDisplayFunc(); // active window draw
	static void MyReshapeFunc(int width, int height); // window reshape
	static void MyKeyboardFunc(unsigned char key, int x, int y); // key press
	static void MySpecialFunc(int key, int x, int y); // special key press
	static void MyMouseFunc(int button, int status, int x, int y); // mouse button press 
	static void MyMotionFunc(int x, int y); // mouse button press and drag
	static void MyPassiveMotionFunc(int x, int y); // mouse drag

private:
	static int g_width; // window size
	static int g_height; // window size
	static int g_volumn; // view volumn

	static float g_view_x; // mouse x
	static float g_view_y; // mouse y

};