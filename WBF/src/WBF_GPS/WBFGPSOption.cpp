#include "stdafx.h"
#include "WBFGPSOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFGPSOption::CWBFGPSOption()
{
	uiPolygonFace = GL_FRONT_AND_BACK;
	uiPolygonMode = GL_FILL;

	fRatio = 0.2f;
}

CWBFGPSOption::~CWBFGPSOption()
{
}