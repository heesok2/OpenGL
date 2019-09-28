#pragma once

#include "..\WBF_LIB\FactoryBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFRndrFactory : public CFactoryBase
{
public:
	static CWBFRndrFactory& GetInstance();

public:
	CWBFRndrFactory();
	virtual ~CWBFRndrFactory();

public:
	virtual BOOL Register(UINT uiType, CRuntimeClass * pRuntime) override;
	virtual void Unregister(UINT uiType) override;
	virtual CFactoryObjectBase * CreateObject(UINT uiType) override;

};

#include "HeaderPost.h"
