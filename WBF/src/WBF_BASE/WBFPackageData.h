#pragma once

#include <map>
#include "WBFDataDefine.h"

#include "..\WBF_LIB\WBFSubject.h"

#include "HeaderPre.h"

class CWBFDocBase;
class CWBFModuleBase;
class __MY_EXT_CLASS__ CWBFPackageData : public CWBFSubject
{
public:
	CWBFPackageData(CWBFDocBase* pDoc);
	virtual ~CWBFPackageData();

public:
	virtual void OnInitial() = 0;
	virtual void OnDestroy() = 0;

	virtual CWBFModuleBase* GetModule(DTYPE dbType) = 0;

public:
	virtual BOOL Start();
	virtual BOOL Commit();
	virtual BOOL Rollback();

protected:
	CWBFDocBase* m_pMyDoc;
	std::map<DTYPE, CWBFModuleBase*> m_mModule;

};

#include "HeaderPost.h"
