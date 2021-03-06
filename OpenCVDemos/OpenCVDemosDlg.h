
// OpenCVDemosDlg.h : header file
//

#pragma once
#include "CDlgHighGUI.h"
#include "CDlgIO.h"
#include "CDlgImgCodec.h"
#include "CDlgImgProc.h"

#define MAX_TAB_CNT		(64)

// COpenCVDemosDlg dialog
class COpenCVDemosDlg : public CDialog
{
// Construction
public:
	COpenCVDemosDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVDEMOS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDialog* m_pDlgArr[MAX_TAB_CNT];
	CTabCtrl m_tabMain;
	int m_nCurTabSel{ 0 };
	CDlgHighGUI m_dlgHighGUI;
	CDlgIO m_dlgIO;
	CDlgImgCodec m_dlgImgCodec;
	CDlgImgProc m_dlgImgProc;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
