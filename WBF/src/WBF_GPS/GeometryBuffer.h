#pragma once

#include "..\WBF_GLCORE\ObjectBuffer.h"

#include "HeaderPre.h"

class CViewHelper;
class __MY_EXT_CLASS__ CGeometryBuffer : public CObjectBuffer
{
public:
	CGeometryBuffer();
	virtual ~CGeometryBuffer();

	DECLARE_DYNAMIC_BUFFER(CGeometryBuffer);

public:
	virtual void GLRelease() override;
	virtual void GLBuild(CViewHelper* pHelper, UINT uiFlag) override;
	virtual long GetObjectBuffer(std::map<UINT, TObjectBuffer>& mObjectBuffer) override;

protected:
	std::map<UINT, TObjectBuffer> m_mObjectBuffer;

};

#include "HeaderPost.h"


