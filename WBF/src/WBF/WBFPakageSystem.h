#pragma once

#include "..\WBF_BASE\PackageData.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFPackageSystem : public CPackageData
{
public:
	CWBFPackageSystem(CWBFDocBase* pDoc);
	virtual ~CWBFPackageSystem();

public:
	virtual void OnInitial() override;
	virtual void OnDestroy() override;

	virtual CModuleBase * GetModule(DTYPE dbType) override;

};
#include "HeaderPost.h"