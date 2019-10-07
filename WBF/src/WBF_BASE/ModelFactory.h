#pragma once

#include "..\WBF_LIB\FactoryBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModelFactory : public CFactoryBase
{
public:
	static CModelFactory& GetInstance();

public:
	CModelFactory();
	virtual ~CModelFactory();

public:
	virtual BOOL Register(UINT uiType, CRuntimeClass * pRuntime) override;
	virtual void Unregister(UINT uiType) override;
	virtual CFactoryObjectBase * CreateObject(UINT uiType) override;

};

#include "HeaderPost.h"

