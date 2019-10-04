#include "stdafx.h"
#include "resource.h"
#include "WBFControlDlg.h"
#include "WBFDoc.h"
#include "WBFView.h"

#include "..\WBF_BASE\PackageData.h"
#include "..\WBF_BASE\ModuleBox.h"

#include "..\WBF_BASE\WBFGraphicDef.h"
#include "..\WBF_BASE\WBFModelDataManager.h"
#include "..\WBF_BASE\WBFModelData.h"
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
	DDX_Control(pDX, IDC_WBF_RATIO_SLID, m_slidRatio);
}

BEGIN_MESSAGE_MAP(CWBFControlDlg, CWBFDialog)
	ON_BN_CLICKED(IDC_UPDATE_BTN, OnClickedUpdate)
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

BOOL CWBFControlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CWBFDialog::PreTranslateMessage(pMsg);
}

void CWBFControlDlg::OnOK()
{
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

	CString aTypeName[] = {_T("Sample")};
	UINT aTypeData[] = {gps::E_GPS_SAMPLE};
	lambda_cobx(m_cobxType, sizeof(aTypeData) / sizeof(UINT), aTypeName, aTypeData);

	CString aPolyFaceName[] = {_T("Front/Back"), _T("Front"), _T("Back")};
	UINT aPolyFaceData[] = {GL_FRONT_AND_BACK , GL_FRONT, GL_BACK,};
	lambda_cobx(m_cobxPolyFace, sizeof(aPolyFaceData) / sizeof(UINT), aPolyFaceName, aPolyFaceData);

	CString aPolyModeName[] = {_T("Fill"), _T("Line")};
	UINT aPolyModeData[] = {GL_FILL, GL_LINE};
	lambda_cobx(m_cobxPolyMode, sizeof(aPolyModeData) / sizeof(UINT), aPolyModeName, aPolyModeData);

	m_slidRatio.SetRange(0, 100);
	m_slidRatio.SetRangeMin(0);
	m_slidRatio.SetRangeMax(100);
	m_slidRatio.SetPos(50);
	m_slidRatio.SetTicFreq(10);
	m_slidRatio.SetLineSize(1);
	m_slidRatio.SetPageSize(10);
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

	//auto pModelMgr = m_pMyDoc->GetModelManager();
	//auto pModel = pModelMgr->GetModel(uiType);
	//auto pOption = (CWBFGPSOption*)pModel->GetOption();

	//pOption->uiPolygonFace = lambda_cobx(m_cobxPolyFace);
	//pOption->uiPolygonMode = lambda_cobx(m_cobxPolyMode);

	//pOption->fRatio = (float)m_slidRatio.GetPos() / 100.f;

	//pModelMgr->OnUpdateOnly((UINT)uiType);

	return TRUE;
}

BOOL CWBFControlDlg::CheckData()
{
	auto lambda_cobx = [](CComboBox& cobx)
	{
		auto item = cobx.GetCurSel();
		return (UINT)cobx.GetItemData(item);
	};

	auto uiType = lambda_cobx(m_cobxType);
	switch (uiType)
	{
	case gps::E_GPS_SAMPLE:
		{

		}
		break;
	default:
		{
			// Unknown
			return FALSE;
		}
		break;
	}

	return TRUE;
}

BOOL CWBFControlDlg::Execute()
{
	if (!Dlg2Data()) return TRUE;

	auto lambda_cobx = [](CComboBox& cobx)
	{
		auto item = cobx.GetCurSel();
		return (UINT)cobx.GetItemData(item);
	};


	auto pPackage = m_pMyDoc->GetPackage();
	if (!pPackage->Start()) return FALSE;

	auto uiType = lambda_cobx(m_cobxType);
	switch (uiType)
	{
	case gps::E_GPS_SAMPLE:
		{
			auto pModuleVertex = pPackage->GetModule(E_TYPE_VERTEX);
			auto pModuleSubBody = pPackage->GetModule(E_TYPE_SUBBODY);
			auto pModuleBody = pPackage->GetModule(E_TYPE_BODY);

			pModuleVertex->SetDefaultData();
			pModuleSubBody->SetDefaultData();
			pModuleBody->SetDefaultData();
		}
		break;
	default:
		break;
	}

	return pPackage->Commit();
}

void CWBFControlDlg::OnClickedUpdate()
{
	if (!Execute())
	{
		// Unknown
	}

	m_pMyDoc->UpdateAllViews(NULL);
}

void CWBFControlDlg::OnDestroy()
{
	CWBFDialog::OnDestroy();
}