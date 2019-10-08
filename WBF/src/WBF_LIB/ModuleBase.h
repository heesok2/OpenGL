#pragma once

#include "HeaderPre.h"

class CPackage;
class __MY_EXT_CLASS__ CModuleBase
{
public:
	CModuleBase(CPackage* pPackage);
	virtual ~CModuleBase();

public:
	virtual UINT GetFlag() { return m_uiFlag; }
	virtual void SetFlag(UINT uiFlag) { m_uiFlag = uiFlag; }

public:
	virtual DTYPE GetDataType() = 0;

	virtual void Clear() = 0;
	virtual void SetDefaultData() = 0;

	virtual DKEY GetNewKey() = 0;


protected:
	UINT m_uiFlag;
	CPackage* m_pPackage;

};

#include "HeaderPost.h"