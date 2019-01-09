#pragma once


// CDlgIO dialog

class CDlgIO : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIO)

public:
	CDlgIO(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgIO();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRect m_rectImg;
	CDC* m_pDC;

	bool m_bStopCap;
	HANDLE m_hThreadCamCap;
	static UINT WINAPI ThreadShowCamCap(LPVOID param);

	UINT m_nCamFPS;
	cv::VideoCapture m_videoCap;

	afx_msg void OnBnClickedButtonCam();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonVideo();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
