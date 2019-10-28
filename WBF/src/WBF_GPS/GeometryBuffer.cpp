#include "stdafx.h"
#include "GeometryBuffer.h"
#include "BufferType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC_OBJECT_BUFFER(CGeometryBuffer, E_BUFFER_GEOMETRY);

CGeometryBuffer::CGeometryBuffer()
{
}


CGeometryBuffer::~CGeometryBuffer()
{
}

void CGeometryBuffer::GLRelease()
{

}

void CGeometryBuffer::GLBuild(CDocument * pDoc, UINT uiFlag)
{
}

long CGeometryBuffer::GetObjectBuffer(std::vector<TObjectBuffer>& lstObjectBuffer)
{
	return 0;
}
