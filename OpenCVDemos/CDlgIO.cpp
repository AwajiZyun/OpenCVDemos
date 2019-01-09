// CDlgIO.cpp : implementation file
//

#include "stdafx.h"
#include "OpenCVDemos.h"
#include "CDlgIO.h"
#include "afxdialogex.h"


// CDlgIO dialog

IMPLEMENT_DYNAMIC(CDlgIO, CDialogEx)

CDlgIO::CDlgIO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IO, pParent)
	, m_bStopCap(false)
	, m_nCamFPS(15)
{

}

CDlgIO::~CDlgIO()
{
}

void CDlgIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgIO, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAM, &CDlgIO::OnBnClickedButtonCam)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_VIDEO, &CDlgIO::OnBnClickedButtonVideo)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgIO message handlers

BOOL CDlgIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemInt(IDC_EDIT_CAM_IDX, 0);
	m_hThreadCamCap = reinterpret_cast<HANDLE>(_beginthreadex(
		nullptr, 0, ThreadShowCamCap, this, 0, nullptr));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIO::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetDlgItem(IDC_STATIC_IMG) && ::IsWindow(GetDlgItem(IDC_STATIC_IMG)->m_hWnd)) {
		CRect rect(POINT{ 10, 50 }, POINT{ cx - 10, cy - 10 });
		GetDlgItem(IDC_STATIC_IMG)->MoveWindow(&rect);

		m_pDC = GetDlgItem(IDC_STATIC_IMG)->GetDC();
		GetDlgItem(IDC_STATIC_IMG)->GetClientRect(&m_rectImg);
		m_pDC->SetStretchBltMode(COLORONCOLOR);
	}
}

UINT WINAPI CDlgIO::ThreadShowCamCap(LPVOID param)
{
	CDlgIO* pDlg = static_cast<CDlgIO*>(param);
	if (!pDlg) {
		return 0;
	}

	cv::Mat camCap;
	CImage img;
	CWnd *pWnd = pDlg->GetDlgItem(IDC_STATIC_IMG);
	pDlg->m_pDC = pWnd->GetDC();
	pWnd->GetClientRect(&pDlg->m_rectImg);
	pDlg->m_pDC->SetStretchBltMode(COLORONCOLOR);

	while (!pDlg->m_bStopCap) {
		try {
			if (pDlg->m_videoCap.isOpened() && pDlg->m_videoCap.read(camCap)) {
				// Create CImage and draw it on the screen
				int width = camCap.cols;
				int height = camCap.rows;
				int channels = camCap.channels();
				img.Destroy();
				img.Create(width, height, 8 * channels);
				UCHAR* ps;
				UCHAR* pimg = (UCHAR*)img.GetBits();
				int step = img.GetPitch();
				for (int i = 0; i < height; ++i) {
					ps = (camCap.ptr<UCHAR>(i));
					for (int j = 0; j < width; ++j) {
						if (channels == 1) {
							*(pimg + i * step + j) = ps[j];
						}
						else if (channels == 3) {
							for (int k = 0; k < 3; ++k) {
								*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
							}
						}
					}
				}
				img.Draw(pDlg->m_pDC->m_hDC, pDlg->m_rectImg);
			}
		}
		catch (cv::Exception ex) {
			cout << "ThreadShowCamCap throw:" << ex.what() << "__" << __LINE__ << endl;
		}
		Sleep(1000 / pDlg->m_nCamFPS);
	}

	return 0;
}

void CDlgIO::OnBnClickedButtonCam()
{
	CString context;
	GetDlgItemTextW(IDC_BUTTON_CAM, context);
	if (0 <= context.Find(L"Open")) {
		// Open specific camera
		int camIdx = GetDlgItemInt(IDC_EDIT_CAM_IDX) + cv::CAP_DSHOW;
		if (cv::CAP_DSHOW > camIdx) {
			return;
		}
		try {
			m_videoCap.open(camIdx);
			if (m_videoCap.isOpened()) {
				m_nCamFPS = 15;
				GetDlgItem(IDC_BUTTON_CAM)->SetWindowTextW(L"Close");
			}
			else {
				::MessageBox(nullptr, L"Open camera failed", L"", MB_ICONERROR);
			}
		}
		catch (cv::Exception ex) {
			cout << "OnBnClickedButtonCam throw:" << ex.what() << "__" << __LINE__ << endl;
		}
	}
	else {
		// Close camera
		try {
			m_videoCap.release();
		}
		catch (cv::Exception ex) {
			cout << "OnBnClickedButtonCam throw:" << ex.what() << "__" << __LINE__ << endl;
		}
		GetDlgItem(IDC_BUTTON_CAM)->SetWindowTextW(L"Open");
	}
}

void CDlgIO::OnBnClickedButtonVideo()
{
	GetDlgItem(IDC_BUTTON_CAM)->SetWindowTextW(L"Open");
	SetDlgItemTextW(IDC_EDIT_VIDEO_PATH, L"");
	CFileDialog dlgFile(TRUE);
	if (IDOK == dlgFile.DoModal()) {
		CString context = dlgFile.GetPathName();
		SetDlgItemTextW(IDC_EDIT_VIDEO_PATH, context);
		char pPath[MAX_PATH] = { 0 };
		int nRet = WideCharToMultiByte(CP_ACP, 0, context, -1, pPath, MAX_PATH, NULL, FALSE);
		try {
			// Warning: Debug Assertion Failed in some string case
			m_videoCap.open(pPath);
			if (m_videoCap.isOpened()) {
				m_nCamFPS = static_cast<UINT>(m_videoCap.get(cv::CAP_PROP_FPS));
			}
			else {
				::MessageBox(nullptr, L"Open video failed", L"", MB_ICONERROR);
			}
		}
		catch (cv::Exception ex) {
			cout << "OnBnClickedButtonVideo throw:" << ex.what() << "__" << __LINE__ << endl;
		}
	}
}

void CDlgIO::OnClose()
{
	// Close camera
	CString context;
	GetDlgItemTextW(IDC_BUTTON_CAM, context);
	if (0 <= context.Find(L"Close")) {
		m_bStopCap = true;
		::WaitForSingleObject(m_hThreadCamCap, INFINITE);
		m_videoCap.release();
	}

	if (m_pDC) {
		ReleaseDC(m_pDC);
	}

	CDialogEx::OnClose();
}

