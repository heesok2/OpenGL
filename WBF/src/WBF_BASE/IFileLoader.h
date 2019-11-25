#pragma once
class IFileLoader
{
public:
	IFileLoader();
	virtual ~IFileLoader();

public:
	virtual BOOL Import(const CString& strFullPath) = 0;

};

