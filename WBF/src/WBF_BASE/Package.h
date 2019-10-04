#pragma once

#include <map>

#include "..\WBF_LIB\WBFSubject.h"

#include "HeaderPre.h"

class CWBFDocBase;
class CModuleBase;
class __MY_EXT_CLASS__ CPackage : public CWBFSubject
{
public:
	CPackage(CWBFDocBase* pDoc);
	virtual ~CPackage();

public:
	virtual void OnInitial() = 0;
	virtual void OnDestroy() = 0;

	virtual CModuleBase* GetModule(DTYPE dbType) = 0;

public:
	virtual BOOL Start();
	virtual BOOL Commit();
	virtual BOOL Rollback();

protected:
	CWBFDocBase* m_pMyDoc;
	std::map<DTYPE, CModuleBase*> m_mModule;

};

#include "HeaderPost.h"
