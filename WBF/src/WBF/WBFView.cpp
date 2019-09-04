// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// WBFView.cpp: CWBFView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WBF.h"
#endif

#include "WBFDoc.h"
#include "WBFView.h"

#include "..\WBF_GPS\WBFRndrManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWBFView

IMPLEMENT_DYNCREATE(CWBFView, CWBFViewBase)

BEGIN_MESSAGE_MAP(CWBFView, CWBFViewBase)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CWBFViewBase::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CWBFViewBase::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWBFView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CWBFView 생성/소멸

CWBFView::CWBFView() noexcept
	: m_pRndrMgr(nullptr)
{
}

CWBFView::~CWBFView()
{
}

BOOL CWBFView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CWBFViewBase::PreCreateWindow(cs);
}

// CWBFView 그리기

void CWBFView::OnDraw(CDC* pDC)
{
	CWBFViewBase::OnDraw(pDC);

	CWBFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	BeginwglCurrent();
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		m_pRndrMgr->GLDrawScen();


		SwapBuffers();
	}
	EndwglCurrent();
}


// CWBFView 인쇄


void CWBFView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWBFView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWBFView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWBFView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CWBFView::OnInitialUpdate()
{
	CWBFViewBase::OnInitialUpdate();

	auto pDoc = static_cast<CWBFDoc*>(GetDocument());
	if (pDoc == nullptr) return;

	m_pRndrMgr = new CWBFRndrManager();
	m_pRndrMgr->OnInitialUpdate();
}

void CWBFView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWBFView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWBFView 진단

#ifdef _DEBUG
void CWBFView::AssertValid() const
{
	CWBFViewBase::AssertValid();
}

void CWBFView::Dump(CDumpContext& dc) const
{
	CWBFViewBase::Dump(dc);
}

CWBFDoc* CWBFView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWBFDoc)));
	return (CWBFDoc*)m_pDocument;
}
#endif //_DEBUG


// CWBFView 메시지 처리기


int CWBFView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWBFViewBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CWBFView::OnDestroy()
{
	if (m_pRndrMgr != nullptr)
	{
		m_pRndrMgr->OnDestroy();
		_SAFE_DELETE(m_pRndrMgr);
	}

	CWBFViewBase::OnDestroy();
}
