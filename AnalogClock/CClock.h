#pragma once
#include <afxwin.h>

class CClock : public CWnd
{
protected:
	virtual void PreSubclassWindow();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	void DrawObject();
};

