#include "stdafx.h"
#include "resource.h"
#include "WBFControlDlg.h"

CWBFControlDlg::CWBFControlDlg(CWBFDocBase * pDoc, CWBFViewBase * pView, CWnd * pParent)
	: CWBFDialog(CWBFControlDlg::IDD, pDoc, pParent), m_pView(pView)
{
}

CWBFControlDlg::~CWBFControlDlg()
{
}

void CWBFControlDlg::DoDataExchange(CDataExchange * pDX)
{
	CWBFDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWBFControlDlg, CWBFDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CWBFControlDlg::Create(CWnd * pParent)
{
	return CWBFDialog::Create(CWBFControlDlg::IDD, pParent);
}

BOOL CWBFControlDlg::OnInitDialog()
{
	CWBFDialog::OnInitDialog();


	return TRUE;
}

void CWBFControlDlg::OnDestroy()
{
	CWBFDialog::OnDestroy();
}
