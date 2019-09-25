#pragma once

#include "..\WBF_BASE\WBFPackageData.h"

class CWBFPackageSystem : public CWBFPackageData
{
public:
	CWBFPackageSystem();
	virtual ~CWBFPackageSystem();

public:
	// CWBFDataPackage을(를) 통해 상속됨
	virtual void OnInitial() override;
	virtual void OnDestroy() override;
	virtual CWBFModuleBase * GetModule(DTYPE dbType) override;

};

