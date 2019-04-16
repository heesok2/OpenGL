#include <iostream>
#include <cassert>
#include "RndrSample.h"
#include "RndrGlut.h"
#include "RndrModeling.h"

enum GL_RNDR_TYPE
{
	GL_RNDR_SAMPLE = 0,
	GL_RNDR_GLUT,
	GL_RNDR_MODELING,
	GL_RNDR_NUM
};

int main(int argc, char **argv)
{
	GL_RNDR_TYPE eType = GL_RNDR_MODELING;
	switch (eType)
	{
	case GL_RNDR_SAMPLE: { CRndrSample rndr; rndr.Run(); } break;
	case GL_RNDR_GLUT: { CRndrGlut rndr; rndr.Run(); } break;
	case GL_RNDR_MODELING: { CRndrModeling rndr; rndr.Run(); } break;
	}

	return 0;
}