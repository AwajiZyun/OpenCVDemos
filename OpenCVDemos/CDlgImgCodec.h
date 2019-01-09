#pragma once


// CDlgImgCodec dialog

class CDlgImgCodec : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgCodec)

public:
	CDlgImgCodec(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgImgCodec();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMG_CODEC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDC* m_pDC;
	CRect m_rectImg;

	cv::Mat m_matImg;

	afx_msg void OnBnClickedButtonInport();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
};
