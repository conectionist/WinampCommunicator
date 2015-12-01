
// TesterWithGUIDlg.h : header file
//

#pragma once

#include <WinampCommunicator.h>
#include "afxcmn.h"

// CTesterWithGUIDlg dialog
class CTesterWithGUIDlg : public CDialogEx
{
// Construction
public:
	CTesterWithGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTERWITHGUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	WinampCommunicator winampCom;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_Slider;
};
