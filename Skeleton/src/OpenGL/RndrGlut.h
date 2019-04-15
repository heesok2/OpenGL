#pragma once

#include "IRndrBase.h"

class CRndrGlut : public IRndrBase
{
public:
	CRndrGlut();
	virtual ~CRndrGlut();

public:
	virtual bool Run() override;

public:
	static void MyDisplayFunc(); // active window draw
	static void MyReshapeFunc(int width, int height); // window reshape
	static void MyKeyboardFunc(unsigned char key, int x, int y); // key pressure
	static void MySpecialFunc(int key, int x, int y); // special key

};

