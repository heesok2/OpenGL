#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"

#include "WBFVBODefine.h"
#include "WBFVBOFactory.h"

#include "HeaderPre.h"

class CWBFDocBase;
class __MY_EXT_CLASS__ CWBFVBOData : public CFactoryObjectBase 
{
public:
	CWBFVBOData();
	virtual ~CWBFVBOData();

public:
	virtual UINT GetType() override { ASSERT(g_warning); return 0; }
	virtual void ProcessData(CWBFDocBase* pDoc) = 0;

};

#include "HeaderPost.h"

#define DECLARE_VBO(class_name)\
DECLARE_DYNCREATE(class_name);

#define IMPLEMENT_VBO(type, class_name)\
IMPLEMENT_DYNCREATE(class_name, CWBFVBOData);\
BOOL b##class_name = CWBFVBOFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));