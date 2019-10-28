#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"
#include "ObjectBufferFactory.h"

#include "HeaderPre.h"

typedef struct tagObjectBuffer
{
	UINT uiKey; // Primary key

	UINT uiVAO;
	UINT uiVBO;
	UINT uiEBO;
	UINT uiDataSize;

	tagObjectBuffer(UINT _uiVAO = 0, UINT _uiVBO = 0, UINT _uiEBO = 0, UINT _uiDataSize = 0)
		: uiKey(0), uiVAO(_uiVAO), uiVBO(_uiVBO), uiEBO(_uiEBO), uiDataSize(_uiDataSize)
	{}

} TObjectBuffer, *LPObjectBuffer;

class __MY_EXT_CLASS__ CObjectBuffer : public CFactoryObjectBase
{
public:
	CObjectBuffer();
	virtual ~CObjectBuffer();

public:
	virtual void GLRelease() = 0;
	virtual void GLBuild(CDocument* pDoc, UINT uiFlag) = 0;
	virtual long GetObjectBuffer(std::vector<TObjectBuffer>& lstObjectBuffer) = 0;
	
};

#include "HeaderPost.h"

#define DECLARE_DYNAMIC_BUFFER(class_name)\
DECLARE_DYNCREATE(class_name);\
virtual UINT GetType() override;

#define IMPLEMENT_DYNAMIC_BUFFER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CObjectBuffer);\
UINT class_name::GetType() { return type; }\
BOOL b##class_name = CObjectBufferFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));