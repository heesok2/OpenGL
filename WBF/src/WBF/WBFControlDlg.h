#pragma once

#include "..\WBF_BASE\WBFDialog.h"

class CWBFViewBase;
class CWBFControlDlg : public CWBFDialog
{
public:
	CWBFControlDlg(CWBFDocBase* pDoc, CWBFViewBase* pView, CWnd* pParent = nullptr);
	virtual ~CWBFControlDlg();

	enum { IDD = IDD_WBF_CONTROL_DLG };

public:
	BOOL Create(CWnd* pParent = nullptr);

private:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

private:
	void SetControl();
	void Data2Dlg();
	BOOL Dlg2Data();
	BOOL CheckData();

private:
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP();

private:
	CWBFViewBase* m_pView;
	
	CComboBox m_cobxType;

	// Polygon Option
	CComboBox m_cobxPolyFace;
	CComboBox m_cobxPolyMode;

	// Value
	CSliderCtrl m_slidRatio;

public:
};