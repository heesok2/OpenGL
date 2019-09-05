#pragma once
class CWBFCategoryBase
{
public:
	CWBFCategoryBase();
	virtual ~CWBFCategoryBase();

public:
	virtual void OnInitialUpdate(CMFCRibbonBar* pRibbonBar) = 0;
};

