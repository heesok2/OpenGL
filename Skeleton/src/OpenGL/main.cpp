#include <iostream>
#include <cassert>
#include "RndrSample.h"


enum GL_RNDR_TYPE
{
	GL_RNDR_SAMPLE = 0,
	GL_RNDR_NUM
};

IRndrBase* GetRndr(GL_RNDR_TYPE eType)
{
	IRndrBase* pRndr = nullptr;

	switch (eType)
	{
	case GL_RNDR_SAMPLE: pRndr = new CRndrSample; break;
	default:
	{
		assert(false);
		pRndr = new CRndrSample;
	}
	break;
	}

	return pRndr;
}

int main(int argc, char **argv)
{
	GL_RNDR_TYPE eType = GL_RNDR_SAMPLE;
	switch (eType)
	{
	case GL_RNDR_SAMPLE: { CRndrSample rndr; rndr.Run(); } break;
	}

	return 0;
}