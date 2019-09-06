#pragma once

#include "HeaderPre.h"

class CWBFDocBase;
class __MY_EXT_CLASS__ CWBFDialog : public CDialog
{
public:
	CWBFDialog(CWBFDocBase* pDoc, CWnd* pParent = nullptr);
	CWBFDialog(UINT uiResID, CWBFDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CWBFDialog();

public:
	virtual INT_PTR DoModal();

protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();

protected:
	BOOL m_bModeless; // default true
	CWBFDocBase* m_pMyDoc;
};

#include "HeaderPost.h"