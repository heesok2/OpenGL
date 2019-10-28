#pragma once

#include "..\WBF_GLCORE\ObjectBuffer.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CGeometryBuffer : public CObjectBuffer
{
public:
	CGeometryBuffer();
	virtual ~CGeometryBuffer();

	DECLARE_DYNAMIC_OBJECT_BUFFER(CGeometryBuffer);

public:
	virtual void GLRelease() override;
	virtual void GLBuild(CDocument * pDoc, UINT uiFlag) override;
	virtual long GetObjectBuffer(std::vector<TObjectBuffer>& lstObjectBuffer) override;

protected:
	std::vector<TObjectBuffer> m_lstObjectBuffer;
};

#include "HeaderPost.h"


