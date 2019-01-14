#pragma once
#define IMG_PROC_TYPE_FILTERING			(0)

// CDlgImgProc dialog

class CDlgImgProc : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgProc)

public:
	CDlgImgProc(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgImgProc();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMGPROC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	cv::Mat m_matImg;
	CDC* m_pDC;
	CRect m_rectImg;

	int m_nImgProcType;
	ULONG DrawMatImg(cv::Mat& mat);

	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CComboBox m_comboFilter;
	afx_msg void OnCbnSelchangeComboFiltering();
	CSliderCtrl m_slider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CComboBox m_comboGeometric;
	afx_msg void OnCbnSelchangeComboGeometric();
	CComboBox m_comboMiscellaneous;
	afx_msg void OnCbnSelchangeComboMiscellanceous();
	CComboBox m_comboDrawing;
	afx_msg void OnCbnSelchangeComboDrawing();
	CComboBox m_comboSubdivision;
	afx_msg void OnCbnSelchangeComboSubdivision();
	CComboBox m_comboHistogram;
	afx_msg void OnCbnSelchangeComboHistograms();
	CComboBox m_comboFeature;
	afx_msg void OnCbnSelchangeComboFeatures();
};
