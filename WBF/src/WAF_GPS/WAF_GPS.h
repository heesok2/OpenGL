// WAF_GPS.h : WAF_GPS DLL의 주 헤더 파일
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CWAFGPSApp
// 이 클래스 구현에 대해서는 WAF_GPS.cpp를 참조하세요.
//

class CWAFGPSApp : public CWinApp
{
public:
	CWAFGPSApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
