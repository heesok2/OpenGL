#include "stdafx.h"
#include "resource.h"
#include "WBFControlDlg.h"

CWBFControlDlg::CWBFControlDlg(CWBFViewBase * pViewBase)
	: m_pView(pViewBase)
{
}

CWBFControlDlg::~CWBFControlDlg()
{
}

void CWBFControlDlg::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWBFControlDlg, CDialog)

	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CWBFControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();




	return TRUE;
}

void CWBFControlDlg::PostNcDestroy()
{
	delete this;
	CDialog::PostNcDestroy();
}

BOOL CWBFControlDlg::Create(CWnd * pParent)
{
	return CDialog::Create(CWBFControlDlg::IDD, pParent);
}

void CWBFControlDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
