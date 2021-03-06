
// OpenCVDemosDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenCVDemos.h"
#include "OpenCVDemosDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COpenCVDemosDlg dialog



COpenCVDemosDlg::COpenCVDemosDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OPENCVDEMOS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCVDemosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabMain);
}

BEGIN_MESSAGE_MAP(COpenCVDemosDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &COpenCVDemosDlg::OnTcnSelchangeTab1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COpenCVDemosDlg message handlers

BOOL COpenCVDemosDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize Tab pages
	m_dlgHighGUI.Create(IDD_DIALOG_HIGHGUI, &m_tabMain);
	m_dlgIO.Create(IDD_DIALOG_IO, &m_tabMain);
	m_dlgImgCodec.Create(IDD_DIALOG_IMG_CODEC, &m_tabMain);
	m_dlgImgProc.Create(IDD_DIALOG_IMGPROC, &m_tabMain);
	m_pDlgArr[0] = &m_dlgHighGUI;
	m_pDlgArr[1] = &m_dlgIO;
	m_pDlgArr[2] = &m_dlgImgCodec;
	m_pDlgArr[3] = &m_dlgImgProc;

	m_tabMain.InsertItem(0, L"HighGUI");
	m_tabMain.InsertItem(1, L"VideoIO");
	m_tabMain.InsertItem(2, L"ImgCodec");
	m_tabMain.InsertItem(3, L"ImgProc");
	CRect rc;
	m_tabMain.GetClientRect(rc);
	rc.top += 22;
	rc.bottom -= 2;
	rc.left += 1;
	rc.right -= 3;
	m_dlgHighGUI.MoveWindow(&rc);
	m_dlgIO.MoveWindow(&rc);
	m_dlgImgCodec.MoveWindow(&rc);
	m_dlgImgProc.MoveWindow(&rc);
	m_dlgHighGUI.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenCVDemosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenCVDemosDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenCVDemosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenCVDemosDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_pDlgArr[m_nCurTabSel]->ShowWindow(SW_HIDE);
	m_nCurTabSel = m_tabMain.GetCurSel();
	m_pDlgArr[m_nCurTabSel]->ShowWindow(SW_SHOW);
	*pResult = 0;
}


void COpenCVDemosDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (SIZE_MINIMIZED != nType) {
		if (::IsWindow(m_tabMain.m_hWnd)) {
			// Adjust Tab control
			CRect rect(POINT{ 0, 0 }, POINT{ cx, cy });
			m_tabMain.MoveWindow(&rect);
			// Adjust sub dialog
			for (UINT idx = 0; idx < MAX_TAB_CNT; idx++) {
				if (m_pDlgArr[idx] && m_pDlgArr[idx]->IsWindowVisible()) {
					CRect rectSub(POINT{ 1, 22 }, POINT{ cx - 3, cy - 2 });
					m_pDlgArr[idx]->MoveWindow(&rectSub);
				}
			}
		}
	}
}
