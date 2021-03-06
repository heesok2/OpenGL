#pragma once

#include "..\WBF_LIB\Package.h"

#include "HeaderPre.h"

class CDocBase;
class __MY_EXT_CLASS__ CWBFPackage : public CPackage
{
public:
	CWBFPackage(CDocBase* pDoc);
	virtual ~CWBFPackage();

public:
	virtual void OnInitial() override;
	virtual void OnDestroy() override;

	virtual CModuleBase * GetModule(DTYPE dbType) override;

};

#include "HeaderPost.h"