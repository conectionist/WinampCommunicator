
// TesterWithGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TesterWithGUI.h"
#include "TesterWithGUIDlg.h"
#include "afxdialogex.h"

#include <cstdlib>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTesterWithGUIDlg dialog



CTesterWithGUIDlg::CTesterWithGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTesterWithGUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTesterWithGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
}

BEGIN_MESSAGE_MAP(CTesterWithGUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CTesterWithGUIDlg::OnBnClickedButtonNext)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CTesterWithGUIDlg message handlers

BOOL CTesterWithGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Slider.SetRangeMin(0, false);
	m_Slider.SetRangeMax(100, false);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTesterWithGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTesterWithGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTesterWithGUIDlg::OnBnClickedButtonNext()
{
	try
	{
		winampCom.NextTrack();
	}
	catch(NotRunningException)
	{

	}
}

void CTesterWithGUIDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString m_SliderValue;

	if (nSBCode == SB_THUMBPOSITION) {
		m_SliderValue.Format(L"Volume: %ld", nPos);
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(m_SliderValue);
		UpdateData(false);

		winampCom.SetVolume(nPos);
	}

	else {
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
