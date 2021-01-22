#include "pch.h"
#include "CClock.h"

#define	PI			3.14159265
#define TIMER_ID	(WM_USER + 0x1000)

void CClock::PreSubclassWindow()
{
	this->SetTimer(TIMER_ID, 50, nullptr);

	CWnd::PreSubclassWindow();
}

BEGIN_MESSAGE_MAP(CClock, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CClock::OnPaint()
{
	CPaintDC dc(this);

	if (this->GetSafeHwnd())
	{
		this->DrawObject();
	}
}

void CClock::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID)
	{
		this->Invalidate(FALSE);
	}

	CWnd::OnTimer(nIDEvent);
}

void CClock::DrawObject()
{
	CDC* pDC = this->GetDC();
	CDC memDC;
	CBitmap memBmp;
	CRect rc;

	this->GetClientRect(rc);
	memDC.CreateCompatibleDC(pDC);
	memBmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	memDC.SelectObject(&memBmp);

	memDC.FillSolidRect(rc, ::GetSysColor(COLOR_BTNFACE));

	CRect rcClock(0, 0, rc.Height(), rc.Height());
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush brs(RGB(255, 255, 255));
	CPen* pOldPen = memDC.SelectObject(&pen);
	CBrush* pOldBrs = memDC.SelectObject(&brs);
	memDC.Ellipse(rcClock);

	double r = rc.Height() / 2;
	double l = r * 0.1;

	for (double i = 0; i < 2 * PI; i += 2 * PI / 12)
	{
		memDC.MoveTo(r + (r - l) * cos(i), r - (r - l) * sin(i));
		memDC.LineTo(r + r * cos(i), r - r * sin(i));
	}

	CTime now = CTime::GetCurrentTime();
	int h = now.GetHour() % 12;
	int m = now.GetMinute();
	int s = now.GetSecond();

	double hl = r * 0.7;
	double ml = r * 0.8;
	double sl = r * 0.9;

	double hr = -2 * PI / 12 * h + PI / 2;
	double mr = -2 * PI / 60 * m + PI / 2;
	double sr = -2 * PI / 60 * s + PI / 2;

	memDC.MoveTo(r, r);
	memDC.LineTo(r + hl * cos(hr), r - hl * sin(hr));
	memDC.MoveTo(r, r);
	memDC.LineTo(r + ml * cos(mr), r - ml * sin(mr));
	memDC.MoveTo(r, r);
	memDC.LineTo(r + sl * cos(sr), r - sl * sin(sr));

	pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.DeleteDC();
	memBmp.DeleteObject();
	this->ReleaseDC(pDC);
}
