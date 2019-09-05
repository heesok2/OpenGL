#pragma once

class CWBFViewBase;
class CWBFControlDlg : public CDialog
{
public:
	CWBFControlDlg(CWBFViewBase* pViewBase);
	virtual ~CWBFControlDlg();

	enum { IDD = IDD_WBF_CONTROL_DLG };

private:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();   // default to delete this.

public:
	BOOL Create(CWnd* pParent);


private:
	DECLARE_MESSAGE_MAP();

private:
	CWBFViewBase* m_pView;

public:
	afx_msg void OnDestroy();
};

