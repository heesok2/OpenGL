#include "stdafx.h"
#include "resource.h"
#include "WBFControlDlg.h"
#include "WBFDoc.h"
#include "WBFView.h"

#include "..\WBF_BASE\WBFGraphicDef.h"
#include "..\WBF_BASE\WBFModelBaseManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

	DDX_Control(pDX, IDC_WBF_TYPE_COBX, m_cobxType);
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

	SetControl();

	Data2Dlg();

	return TRUE;
}

void CWBFControlDlg::OnOK()
{
	if (!Dlg2Data())
		return;

	//CWBFDialog::OnOK();
}

void CWBFControlDlg::OnCancel()
{
	CWBFDialog::OnCancel();
}

void CWBFControlDlg::SetControl()
{
	CString aName[gps::E_GPS_NUM] =
	{
		_T("Sample")
	};

	m_cobxType.ResetContent();
	for (long indx = 0; indx < gps::E_GPS_NUM; ++indx)
	{
		auto item = m_cobxType.AddString(aName[indx]);
		m_cobxType.SetItemData(item, indx);
	}
	m_cobxType.SetCurSel(0);
}

void CWBFControlDlg::Data2Dlg()
{

}

BOOL CWBFControlDlg::Dlg2Data()
{
	if (!CheckData())
		return FALSE;

	auto item = m_cobxType.GetCurSel();
	auto dwItemData = m_cobxType.GetItemData(item);

	auto pModelMgr = m_pMyDoc->GetModelManager();
	pModelMgr->OnUpdateOnly((UINT)dwItemData);
	
	return TRUE;
}

BOOL CWBFControlDlg::CheckData()
{
	return TRUE;
}

void CWBFControlDlg::OnDestroy()
{
	CWBFDialog::OnDestroy();
}