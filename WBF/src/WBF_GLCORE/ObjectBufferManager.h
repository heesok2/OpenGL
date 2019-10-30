#pragma once

#include "HeaderPre.h"

class CObjectBuffer;
class __MY_EXT_CLASS__ CObjectBufferManager
{
public:
	CObjectBufferManager();
	virtual ~CObjectBufferManager();

public:
	void InitialData(CView* pView);
	void CreateObjectBuffer();

	BOOL Exist(UINT uiType);
	CObjectBuffer* LookUp(UINT uiType);
	
	void GLBuildObjectBuffer(UINT uiFlag);	
	void GLDeleteObjectBuffer();

protected:
	CView* m_pView;
	std::map<UINT, CObjectBuffer*> m_mObjectBuffer;

};

#include "HeaderPost.h"