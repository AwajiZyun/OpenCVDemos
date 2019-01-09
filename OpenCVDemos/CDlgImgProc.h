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
	CDC* m_pDC;
	CRect m_rectImg;

	int m_nImgProcType;

	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CComboBox m_comboFilter;
	afx_msg void OnCbnSelchangeComboFiltering();
	CSliderCtrl m_slider;
};
