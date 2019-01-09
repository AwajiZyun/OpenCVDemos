// CDlgImgCodec.cpp : implementation file
//

#include "stdafx.h"
#include "OpenCVDemos.h"
#include "CDlgImgCodec.h"
#include "afxdialogex.h"


// CDlgImgCodec dialog

IMPLEMENT_DYNAMIC(CDlgImgCodec, CDialogEx)

CDlgImgCodec::CDlgImgCodec(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMG_CODEC, pParent)
{

}

CDlgImgCodec::~CDlgImgCodec()
{
}

void CDlgImgCodec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImgCodec, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INPORT, &CDlgImgCodec::OnBnClickedButtonInport)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgImgCodec::OnBnClickedButtonExport)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgImgCodec message handlers

void CDlgImgCodec::OnSize(UINT nType, int cx, int cy)
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

void CDlgImgCodec::OnClose()
{
	if (m_pDC) {
		ReleaseDC(m_pDC);
	}

	CDialogEx::OnClose();
}


void CDlgImgCodec::OnBnClickedButtonInport()
{
	CFileDialog dlgFile(TRUE);
	if (IDOK == dlgFile.DoModal()) {
		CStringA imgPath = CStringA(dlgFile.GetPathName());
		try {
			m_matImg = cv::imread(imgPath.GetBuffer(), cv::IMREAD_UNCHANGED);
			imgPath.ReleaseBuffer();

			CImage cImg;
			cImg.Create(m_matImg.cols, m_matImg.rows, m_matImg.channels() * 8);
			UCHAR* ps;
			UCHAR* pimg = (UCHAR*)cImg.GetBits();
			int step = cImg.GetPitch();
			for (int i = 0; i < m_matImg.rows; ++i) {
				ps = (m_matImg.ptr<UCHAR>(i));
				for (int j = 0; j < m_matImg.cols; ++j) {
					if (m_matImg.channels() == 1) {
						*(pimg + i * step + j) = ps[j];
					}
					else if (m_matImg.channels() == 3) {
						for (int k = 0; k < 3; ++k) {
							*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
						}
					}
				}
			}
			cImg.Draw(m_pDC->m_hDC, m_rectImg);
		}
		catch (cv::Exception ex) {
			cout << "OnBnClickedButtonInport throw:" << ex.what() << "__" << __LINE__ << endl;
		}
	}
}


void CDlgImgCodec::OnBnClickedButtonExport()
{
	if (m_matImg.data) {
		CFileDialog dlgFile(FALSE);
		if (IDOK == dlgFile.DoModal()) {
			CStringA imgPath = CStringA(dlgFile.GetFolderPath());
			try {
				std::vector<int> vecParams;
				vecParams.push_back(cv::IMWRITE_JPEG_QUALITY);
				vecParams.push_back(90);
				CStringA bmpPath = imgPath + "\\export.bmp";
				CStringA jpgPath = imgPath + "\\export.jpg";
				CStringA pngPath = imgPath + "\\export.png";
				cv::imwrite(bmpPath.GetBuffer(), m_matImg);
				cv::imwrite(jpgPath.GetBuffer(), m_matImg);
				vecParams.push_back(cv::IMWRITE_PNG_COMPRESSION);
				vecParams.push_back(5);
				cv::imwrite(pngPath.GetBuffer(), m_matImg);
				bmpPath.ReleaseBuffer();
				jpgPath.ReleaseBuffer();
				pngPath.ReleaseBuffer();
			}
			catch (cv::Exception ex) {
				cout << "OnBnClickedButtonExport throw:" << ex.what() << "__" << __LINE__ << endl;
			}
		}
	}
}

