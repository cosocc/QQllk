
// QQllkDlg.h: 头文件
//

#pragma once


// CQQllkDlg 对话框
class CQQllkDlg : public CDialogEx
{
// 构造
public:
	CQQllkDlg(CWnd* pParent = nullptr);	// 标准构造函数
   // bool ClearPiar();
// Dialog Data
	//{{AFX_DATA(CLlk_wgDlg)
	enum { IDD = IDD_LLK_WG_DIALOG };
	CButton	m_ctl_cleartime;
	CButton	m_ctl_check;
	CSliderCtrl	m_ctl_slider;
	int		m_x;
	int		m_y;
	UINT	m_num;
	CString	m_chessdata;
	int		m_p1x;
	int		m_p1y;
	int		m_p2x;
	int		m_p2y;
	BOOL	m_autoplay;
	BOOL	m_autostart;
	int		m_sliderNum;
	BOOL	m_sliderenable;
	BOOL	m_gametop;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_WG_DIALOG};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartGame();
	afx_msg void OnButton2();
	afx_msg void OnBtnReadchess();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck3();
	afx_msg void OnCleartimer();
	afx_msg void OnGameTop();
	afx_msg void OnClearAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDestroy();
};
