#include "stdafx.h"
#include "WBFDialog.h"

CWBFDialog::CWBFDialog(CWBFDocBase * pDoc, CWnd * pParent)
	: CDialog(), m_pMyDoc(pDoc), m_bModeless(TRUE)
{
}

CWBFDialog::CWBFDialog(UINT uiResID, CWBFDocBase * pDoc, CWnd * pParent)
	: CDialog(uiResID, pParent), m_pMyDoc(pDoc), m_bModeless(TRUE)
{
}

CWBFDialog::~CWBFDialog()
{
}

INT_PTR CWBFDialog::DoModal()
{
	m_bModeless = FALSE;

	return CDialog::DoModal();
}

void CWBFDialog::OnOK()
{
	CDialog::OnOK();

	if (m_bModeless) CDialog::DestroyWindow();
}

void CWBFDialog::OnCancel()
{
	CDialog::OnCancel();

	if (m_bModeless) CDialog::DestroyWindow();
}

void CWBFDialog::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	
	if (m_bModeless) delete this;
}