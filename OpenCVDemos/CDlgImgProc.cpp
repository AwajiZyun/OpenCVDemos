// CDlgImgProc.cpp : implementation file
//

#include "stdafx.h"
#include "OpenCVDemos.h"
#include "CDlgImgProc.h"
#include "afxdialogex.h"


// CDlgImgProc dialog

IMPLEMENT_DYNAMIC(CDlgImgProc, CDialogEx)

CDlgImgProc::CDlgImgProc(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMGPROC, pParent)
{

}

CDlgImgProc::~CDlgImgProc()
{
}

void CDlgImgProc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILTERING, m_comboFilter);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}


BEGIN_MESSAGE_MAP(CDlgImgProc, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_FILTERING, &CDlgImgProc::OnCbnSelchangeComboFiltering)
END_MESSAGE_MAP()


// CDlgImgProc message handlers

BOOL CDlgImgProc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboFilter.AddString(L"bilateralFilter");
	m_comboFilter.AddString(L"pyrMeanShiftFiltering");
	m_comboFilter.AddString(L"boxFilter");
	m_comboFilter.AddString(L"blur");
	m_comboFilter.AddString(L"GaussianBlur");
	m_comboFilter.AddString(L"medianBlur");
	m_comboFilter.AddString(L"filter2D");
	m_comboFilter.AddString(L"buildPyramid");
	m_comboFilter.AddString(L"dilate");
	m_comboFilter.AddString(L"erode");
	m_comboFilter.AddString(L"Laplacian");
	m_comboFilter.AddString(L"pyrDown");
	m_comboFilter.AddString(L"pyrUp");
	m_comboFilter.AddString(L"Scharr");
	m_comboFilter.AddString(L"Sobel");
	m_comboFilter.AddString(L"sqrBoxFilter");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgImgProc::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}


void CDlgImgProc::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetDlgItem(IDC_STATIC_IMG) && ::IsWindow(GetDlgItem(IDC_STATIC_IMG)->m_hWnd)) {
		CRect rect(POINT{ 10, 120 }, POINT{ cx - 10, cy - 10 });
		GetDlgItem(IDC_STATIC_IMG)->MoveWindow(&rect);

		m_pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC();
		GetDlgItem(IDC_STATIC_IMG)->GetClientRect(&m_rectImg);
		m_pDC->SetStretchBltMode(COLORONCOLOR);
	}
}




void CDlgImgProc::OnCbnSelchangeComboFiltering()
{
	cout << m_comboFilter.GetCurSel() << endl;
}
