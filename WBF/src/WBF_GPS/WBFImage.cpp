#include "stdafx.h"
#include "WBFImage.h"
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


CWBFImage::CWBFImage()
{
	m_pBuffer = nullptr;
	m_nWidth = m_nHeight = m_nBytes = 0;
}

CWBFImage::~CWBFImage()
{
	_SAFE_DELETE_ARRAY(m_pBuffer);
}

void CWBFImage::InitialData(CString strFilePath)
{
	// std::string <-- CString
	std::string str = std::string(CT2CA(strFilePath.operator LPCWSTR()));
	BYTE* data = stbi_load(str.c_str(), &m_nWidth, &m_nHeight, &m_nBytes, 0);

	auto szData = m_nWidth * m_nHeight * m_nBytes;
	m_pBuffer = new BYTE[szData];
	std::copy(data, data + szData, m_pBuffer);

	stbi_image_free(data);
}