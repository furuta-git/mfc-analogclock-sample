﻿#pragma once
#include "CClock.h"

class CAnalogClockDlg : public CDialogEx
{
public:
	CAnalogClockDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANALOGCLOCK_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	CClock m_Clock;
};
