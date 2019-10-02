#pragma once

#include <vector>
#include "HeaderPre.h"

class CWBFDocBase;
class __MY_EXT_CLASS__ CDocListener
{
public:
	static void DoNotifyMsg(CWBFDocBase* pDoc, WPARAM wParam, LPARAM lParam);

public:
	CDocListener();
	virtual ~CDocListener();

public:
	virtual void OnNotifyMsg(CWBFDocBase* pDoc, WPARAM wParam, LPARAM lParam) = 0;

protected:
	static std::vector<CDocListener*> g_lstObject;

};

#include "HeaderPost.h"