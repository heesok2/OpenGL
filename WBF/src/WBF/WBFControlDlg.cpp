#include "stdafx.h"
#include "resource.h"
#include "WBFControlDlg.h"
#include "WBFDoc.h"
#include "WBFView.h"

#include "..\WBF_BASE\WBFGraphicDef.h"
#include "..\WBF_BASE\WBFModelBaseManager.h"
#include "..\WBF_BASE\WBFModelBase.h"
#include "..\WBF_GPS\WBFGPSOption.h"

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
	DDX_Control(pDX, IDC_WBF_POLY_FACE_COBX, m_cobxPolyFace);
	DDX_Control(pDX, IDC_WBF_POLY_MODE_COBX, m_cobxPolyMode);
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

	m_pMyDoc->UpdateAllViews(nullptr);

	//CWBFDialog::OnOK();
}

void CWBFControlDlg::OnCancel()
{
	CWBFDialog::OnCancel();
}

void CWBFControlDlg::SetControl()
{
	auto lambda_cobx = [](CComboBox& cobx, long uiNum, CString aName[], UINT aData[])
	{
		cobx.ResetContent();
		for (auto indx = 0; indx < uiNum; ++indx)
		{
			auto item = cobx.AddString(aName[indx]);
			cobx.SetItemData(item, aData[indx]);
		}
		cobx.SetCurSel(0);
	};

	CString aTypeName[] = { _T("Sample") };
	UINT aTypeData[] = { gps::E_GPS_SAMPLE };
	lambda_cobx(m_cobxType, sizeof(aTypeData) / sizeof(UINT), aTypeName, aTypeData);

	CString aPolyFaceName[] = { _T("Front/Back"), _T("Front"), _T("Back") };
	UINT aPolyFaceData[] = { GL_FRONT_AND_BACK , GL_FRONT, GL_BACK, };
	lambda_cobx(m_cobxPolyFace, sizeof(aPolyFaceData) / sizeof(UINT), aPolyFaceName, aPolyFaceData);

	CString aPolyModeName[] = { _T("Fill"), _T("Line") };
	UINT aPolyModeData[] = { GL_FILL, GL_LINE };
	lambda_cobx(m_cobxPolyMode, sizeof(aPolyModeData) / sizeof(UINT), aPolyModeName, aPolyModeData);
}

void CWBFControlDlg::Data2Dlg()
{

}

BOOL CWBFControlDlg::Dlg2Data()
{
	if (!CheckData())
		return FALSE;

	auto lambda_cobx = [](CComboBox& cobx)
	{
		auto item = cobx.GetCurSel();
		return (UINT)cobx.GetItemData(item);
	};

	auto uiType = lambda_cobx(m_cobxType);

	auto pModelMgr = m_pMyDoc->GetModelManager();
	auto pModel = pModelMgr->GetModel(uiType);
	auto pOption = (CWBFGPSOption*)pModel->GetOption();

	pOption->uiPolygonFace = lambda_cobx(m_cobxPolyFace);
	pOption->uiPolygonMode = lambda_cobx(m_cobxPolyMode);

	pModelMgr->OnUpdateOnly((UINT)uiType);

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