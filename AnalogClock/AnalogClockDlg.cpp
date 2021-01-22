#include "pch.h"
#include "framework.h"
#include "AnalogClock.h"
#include "AnalogClockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAnalogClockDlg::CAnalogClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANALOGCLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnalogClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOCK, m_Clock);
}

BOOL CAnalogClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	CRect rc;
	this->GetClientRect(rc);
	this->m_Clock.MoveWindow(0, 0, rc.Width(), rc.Height());

	return TRUE;
}

BEGIN_MESSAGE_MAP(CAnalogClockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

void CAnalogClockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CAnalogClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
