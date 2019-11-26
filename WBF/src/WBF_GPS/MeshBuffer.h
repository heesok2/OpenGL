#pragma once

#include "..\WBF_GLCORE\ObjectBuffer.h"

#include "HeaderPre.h"

class CViewHelper;
class CEntityMesh;
class __MY_EXT_CLASS__ CMeshBuffer : public CObjectBuffer
{
public:
	CMeshBuffer();
	virtual ~CMeshBuffer();

	DECLARE_DYNAMIC_BUFFER(CMeshBuffer);

public:
	virtual void GLRelease() override;
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) override;
	virtual long GetObjectBuffer(std::map<UINT, TObjectBuffer>& mObjectBuffer) override;

protected:
	UINT GLCreateBuffer(CViewHelper * pHelper, DITER itrMesh, std::map<DKEY, UINT>& mNodeIndx);
	UINT GLCreateIndex(CViewHelper * pHelper, DITER itrMesh, std::map<DKEY, UINT>& mNodeIndx);

protected:
	std::map<UINT, TObjectBuffer> m_mObjectBuffer;

};

#include "HeaderPost.h"