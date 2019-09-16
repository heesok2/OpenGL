#pragma once

#include "HeaderPre.h"

class __MY_EXT_API__ CWBFImage
{
public:
	CWBFImage();
	virtual ~CWBFImage();

public:
	void InitialData(CString strFilePath);

	const BYTE* GetBuffer() { return m_pBuffer; }
	const int GetWidth() { return m_nWidth; }
	const int GetHeight() { return m_nHeight; }
	const int GetBytes() { return m_nBytes; }

protected:
	CString m_strFilePath;
	BYTE* m_pBuffer;
	int m_nWidth;
	int m_nHeight;
	int m_nBytes;
};

#include "HeaderPost.h"