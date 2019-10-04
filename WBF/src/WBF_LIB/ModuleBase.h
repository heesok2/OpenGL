#pragma once

#include "HeaderPre.h"

class CPackage;
class __MY_EXT_CLASS__ CModuleBase
{
public:
	CModuleBase(CPackage* pPackage);
	virtual ~CModuleBase();

public:
	virtual void Clear() = 0;

	virtual DKEY GetNewKey() = 0;
	virtual DTYPE GetDataType() = 0;

	virtual void SetDefaultData() = 0;

protected:
	CPackage* m_pPackage;

};

#include "HeaderPost.h"