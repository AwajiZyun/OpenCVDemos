// CDlgTest.cpp : implementation file
//

#include "stdafx.h"
#include "OpenCVDemos.h"
#include "CDlgHighGUI.h"
#include "afxdialogex.h"


// CDlgTest dialog

IMPLEMENT_DYNAMIC(CDlgHighGUI, CDialogEx)

CDlgHighGUI::CDlgHighGUI(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HIGHGUI, pParent)
{

}

CDlgHighGUI::~CDlgHighGUI()
{
}

void CDlgHighGUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHighGUI, CDialogEx)
//	ON_WM_SIZE()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON_SHOW_WINDOW, &CDlgHighGUI::OnBnClickedButtonShowWindow)
ON_BN_CLICKED(IDC_BUTTON_DESTROY_WINDOW, &CDlgHighGUI::OnBnClickedButtonDestroyWindow)
END_MESSAGE_MAP()


// CDlgTest message handlers




void CDlgHighGUI::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

}


void CDlgHighGUI::OnBnClickedButtonShowWindow()
{
	try {
		cv::Mat mat(300, 400, CV_8UC3, cv::Scalar(255, 255, 255));
		cv::namedWindow("namedWindow", cv::WINDOW_AUTOSIZE);
		cv::setWindowProperty("nameWindow", cv::WINDOW_AUTOSIZE, cv::WND_PROP_AUTOSIZE);

		int nTrackBarValue = 0;
		cv::createTrackbar("trackBar", "namedWindow", &nTrackBarValue, 255, TrackbarCallback);

		cv::setMouseCallback("namedWindow", MouseCallback);

		cv::imshow("namedWindow", mat);
		cv::waitKey(1);
	}
	catch (cv::Exception ex) {
		cout << "OnBnClickedButtonShowWindow throw:" << ex.what() << "__" << __LINE__ << endl;
	}
}

void CDlgHighGUI::OnBnClickedButtonDestroyWindow()
{
	try {
		cv::destroyWindow("namedWindow");
		//cv::destroyAllWindows();
	}
	catch (cv::Exception ex) {
		cout << "OnBnClickedButtonDestroyWindow throw:" << ex.what() << "__" << __LINE__ << endl;
	}
}


// callback functions
void CDlgHighGUI::TrackbarCallback(int pos, void *userdata)
{
	cout << "trackBar value:" << pos << endl;
}

void CDlgHighGUI::MouseCallback(int event, int x, int y, int flags, void *userdata)
{
	switch (event) {
	case cv::EVENT_MOUSEMOVE:
		cout << "mouse pointer move:" << x << "," << y << endl;
		break;
	case cv::EVENT_LBUTTONDOWN:
		cout << "left mouse button is pressed" << endl;
		break;
	case cv::EVENT_RBUTTONDOWN:
		cout << "right mouse button is pressed" << endl;
		break;
	case cv::EVENT_MBUTTONDOWN:
		cout << "middle mouse button is pressed" << endl;
		break;
	case cv::EVENT_LBUTTONUP:
		cout << "left mouse button is released" << endl;
		break;
	case cv::EVENT_RBUTTONUP:
		cout << "right mouse button is released" << endl;
		break;
	case cv::EVENT_MBUTTONUP:
		cout << "middle mouse button is released" << endl;
		break;
	case cv::EVENT_LBUTTONDBLCLK:
		cout << "left mouse button is double clicked" << endl;
		break;
	case cv::EVENT_RBUTTONDBLCLK:
		cout << "right mouse button is double clicked" << endl;
		break;
	case cv::EVENT_MBUTTONDBLCLK:
		cout << "middle mouse button is double clicked" << endl;
		break;
	case cv::EVENT_MOUSEWHEEL:
		cout << "forward or backward scrolling:" << flags << endl;
		break;
	case cv::EVENT_MOUSEHWHEEL:
		cout << "forward and right and left scrolling:" << flags << endl;
		break;
	default:
		break;
	}
}
