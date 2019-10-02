#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"

#include "WBFVBODefine.h"
#include "WBFVBOFactory.h"

#include "HeaderPre.h"

class CWBFDocBase;
class __MY_EXT_CLASS__ CVBOData : public CFactoryObjectBase
{
public:
	CVBOData();
	virtual ~CVBOData();

public:
	virtual void Release() = 0;
	virtual void Build(CWBFDocBase* pDoc) = 0;
	virtual void Draw() = 0;
	
};

#include "HeaderPost.h"

#define DECLARE_DYNAMIC_VBO(class_name)\
DECLARE_DYNCREATE(class_name);

#define IMPLEMENT_DYNAMIC_VBO(type, class_name)\
IMPLEMENT_DYNCREATE(class_name, CVBOData);\
BOOL b##class_name = CWBFVBOFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));