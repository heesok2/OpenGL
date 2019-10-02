#pragma once

#include "..\WBF_BASE\WBFPackageData.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFPackageSystem : public CWBFPackageData
{
public:
	CWBFPackageSystem(CWBFDocBase* pDoc);
	virtual ~CWBFPackageSystem();

public:
	virtual void OnInitial() override;
	virtual void OnDestroy() override;

	virtual CWBFModuleBase * GetModule(DTYPE dbType) override;

};
#include "HeaderPost.h"