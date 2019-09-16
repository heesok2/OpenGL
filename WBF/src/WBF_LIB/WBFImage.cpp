#include "stdafx.h"
#include "WBFImage.h"
#include "WBFString.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CWBFImage::CWBFImage()
{
	m_strFilePath = _T("");
	m_pBuffer = nullptr;
	m_nWidth = m_nHeight = m_nBytes = 0;
}

CWBFImage::~CWBFImage()
{
	_SAFE_DELETE_ARRAY(m_pBuffer);
}

void CWBFImage::InitialData(CString strFilePath)
{
	m_strFilePath = strFilePath;

	std::string conv;
	CWBFString::CSTR2STR(strFilePath, conv);

	stbi_set_flip_vertically_on_load(true);
	BYTE* data = stbi_load(conv.c_str(), &m_nWidth, &m_nHeight, &m_nBytes, 0);
	{
		auto szData = m_nWidth * m_nHeight * m_nBytes;
		m_pBuffer = new BYTE[szData];
		std::copy(data, data + szData, m_pBuffer);
	}
	stbi_image_free(data);
}