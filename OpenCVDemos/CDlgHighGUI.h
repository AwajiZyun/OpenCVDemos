#pragma once


// CDlgTest dialog

class CDlgHighGUI : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHighGUI)

public:
	CDlgHighGUI(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgHighGUI();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonShowWindow();

	static void TrackbarCallback(int pos, void *userdata);
	static void MouseCallback(int event, int x, int y, int flags, void *userdata);
	afx_msg void OnBnClickedButtonDestroyWindow();
};
