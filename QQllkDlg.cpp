
// QQllkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "QQllk.h"
#include "QQllkDlg.h"
#include "afxdialogex.h"
#include "GameProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//CWinApp* aPP;

// CQQllkDlg 对话框



CQQllkDlg::CQQllkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LLK_WG_DIALOG, pParent)
{
	m_x = 0;
	m_y = 0;
	m_num = 0;
	m_chessdata = _T("");
	m_p1x = 0;
	m_p1y = 0;
	m_p2x = 0;
	m_p2y = 0;
	m_autoplay;
	m_autostart = FALSE;
	m_sliderNum = 0;
	m_sliderenable = FALSE;
	m_gametop = FALSE;


	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CQQllkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLEARTIMER, m_ctl_cleartime);
	DDX_Control(pDX, IDC_CHECK3, m_ctl_check);
	DDX_Control(pDX, IDC_SLIDER1, m_ctl_slider);
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDX_Text(pDX, IDC_EDIT4, m_chessdata);
	DDX_Text(pDX, IDC_EDIT5, m_p1x);
	DDX_Text(pDX, IDC_EDIT6, m_p1y);
	DDX_Text(pDX, IDC_EDIT7, m_p2x);
	DDX_Text(pDX, IDC_EDIT8, m_p2y);
	DDX_Check(pDX, IDC_CHECK1, m_autoplay);
	DDX_Check(pDX, IDC_CHECK2, m_autostart);
	DDX_Slider(pDX, IDC_SLIDER1, m_sliderNum);
	DDX_Check(pDX, IDC_CHECK3, m_sliderenable);
	DDX_Check(pDX, IDC_CHECK4, m_gametop);
}

BEGIN_MESSAGE_MAP(CQQllkDlg, CDialogEx)
	//ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnStartGame)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BTN_READCHESS, OnBtnReadchess)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CLEARTIMER, OnCleartimer)
	ON_BN_CLICKED(IDC_CHECK4, OnGameTop)
	ON_BN_CLICKED(IDC_BUTTON5, OnClearAll)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CQQllkDlg 消息处理程序

BOOL CQQllkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MoveWindow(0, 0, 410, 389, true);
	this->m_ctl_slider.SetRange(50, 3000);
	this->m_ctl_slider.SetTicFreq(150);
	this->m_ctl_slider.SetPos(1000);
	this->m_ctl_check.SetCheck(true);
	
	m_autoplay = theApp.GetProfileInt("Place", "自动挂机", 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//void CQQllkDlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
//}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQllkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQllkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CQQllkDlg::OnStartGame()
{
	startGame();
}

void CQQllkDlg::OnButton2()
{
	// 游戏窗口标题："QQ游戏 - 连连看角色版"
// 1、FindWindow               //获取窗口句柄
//2、GetWindowThreadProcessId //获取窗口进程ID
//3、OpenProcess              //打开指定进程
//4、ReadProcessMemory        //读指定进程 内存数据
  //获取窗口句柄
	HWND gameh = ::FindWindow(NULL, gameCaption);
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//打开指定进程
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//读指定进程 内存数据
	SIZE_T byread;
	LPCVOID pbase = (LPCVOID)0x001815FC;   //座位号
	LPVOID  nbuffer = (LPVOID)&m_num;
	::ReadProcessMemory(processH, pbase, nbuffer, 4, &byread);
	UpdateData(false); //更新变量的值到 编辑框
}

void CQQllkDlg::OnBtnReadchess()
{
	// TODO: Add your control notification handler code here
	//获取窗口句柄
	HWND gameh = ::FindWindow(NULL, gameCaption);
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh, &processid);
	//打开指定进程
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	//读指定进程 内存数据
	SIZE_T byread;
	LPCVOID pbase = (LPCVOID)0x00199F5C; //棋盘数据基址
	LPVOID  nbuffer = (LPVOID)&chessdata;    //存放棋盘数据
	::ReadProcessMemory(processH, pbase, nbuffer, 11 * 19, &byread);
	///显示棋盘数据
	char buf[11];
	m_chessdata = ""; //清空编辑
	for (int y = 0; y <= 10; y++)
	{
		for (int x = 0; x <= 18; x++) //读一行
		{
			sprintf_s(buf, sizeof(buf), "%02X ", chessdata[y][x]);
			//_itoa_s(chessdata[y][x], buf, 16); //转换成字串
			m_chessdata += buf;
			m_chessdata += " ";
		}
		//换行
		m_chessdata += "\r\n";
	}
	UpdateData(false);
}

void CQQllkDlg::OnButton3()
{
	// TODO: Add your control notification handler code here
	int   x = 36, y = 244;
	//棋子高宽  44 39
	HWND hwnd = ::FindWindow(NULL, gameCaption);
	int lparam;
	int a = 0, b = 0;
	lparam = ((y +44*b)<< 16) + (x + 39 * a);//表示指定格
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);  // 

}

bool ClearPiar() //消除一对棋子
{
	//读出棋盘数据至chessdata 11,19
	updatdChess();
	//遍历整个棋盘 找出相同类型 一对棋子
	POINT p1, p2;
	int x1, y1, x2, y2;
	for (y1 = 0; y1 < 11; y1++)
		for (x1 = 0; x1 < 19; x1++)
		{
			for (y2 = y1; y2 < 11; y2++)
				for (x2 = 0; x2 < 19; x2++)
					if ((chessdata[y1][x1] == chessdata[y2][x2]) // 棋子1与棋子2 类型是否相同
						&& (!((x1 == x2) && (y1 == y2)))  //要求点1与点2 相等则假
						)
					{
						p1.x = x1; p1.y = y1;
						p2.x = x2; p2.y = y2;
						//检测 相同的2个棋子是否可消掉
						if (Check2p(p1, p2))//如果可消除 则返回真
						{
							//click2p 鼠标模拟 点击 p1，p2
							Click2p(p1, p2);
							/* m_p1x=x1;
							 m_p1y=y1;
							 m_p2x=x2;
							 m_p2y=y2;
							 UpdateData(false);//更新数据至窗口
							 */
							return true;

						}
					}
		}
	return false;
}

void CQQllkDlg::OnButton4()
{
	ClearPiar();
}

VOID CALLBACK playproc(
	HWND hwnd,     // handle of window for timer messages
	UINT uMsg,     // WM_TIMER message
	UINT_PTR idEvent,  // timer identifier
	DWORD dwTime   // current system time
)
{
	ClearPiar();
}
VOID CALLBACK strartproc(
	HWND hwnd,     // handle of window for timer messages
	UINT uMsg,     // WM_TIMER message
	UINT_PTR idEvent,  // timer identifier
	DWORD dwTime   // current system time
)
{
	HWND gameh = ::FindWindow(NULL, gameCaption);
	//AfxMessageBox("Findwindow");
	if (gameh == 0) { return; } //没有找到游戏窗口
	//让游戏窗口置顶
	if (gametop)
	{
		SetWindowPos(gameh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowPos(gameh, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	}


	//
	DWORD pid;
	::GetWindowThreadProcessId(gameh, &pid);
	long flag;
    SIZE_T byReadSize;
	HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	//0x01c3a7B4  开局状态
	::ReadProcessMemory(hp, (LPCVOID)(0x00181F04), (LPVOID)(&flag), 4, &byReadSize);
	if (byReadSize == 0) { AfxMessageBox("未成功读出数据"); }
	if ((flag == 0) && (byReadSize > 0)) { startGame(); } //自动开局
}

const auto PLAYID = 111;
const auto STARTID = 112;
void CQQllkDlg::OnCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//更新窗口内容至变量
	//自动挂机
	if (m_autoplay)
	{

		SetTimer(PLAYID, 1500, &playproc);
	}
	else
	{
		KillTimer(PLAYID);
	}
}

void CQQllkDlg::OnCheck2()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//更新窗口内容至变量
	//自动开局
	if (m_autostart)
	{
		SetTimer(STARTID, 3 * 1000, &strartproc);
	}
	else
	{
		KillTimer(STARTID);
	}
}

void CQQllkDlg::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	// m_num=m_sliderNum;
	m_num = this->m_ctl_slider.GetPos();
	UpdateData(false);
	*pResult = 0;
}

void CQQllkDlg::OnCheck3()
{
	UpdateData(true);
	::EnableWindow(m_ctl_slider.m_hWnd, m_sliderenable);
}

void CQQllkDlg::OnCleartimer()
{
	if (ClearCode()) { m_ctl_cleartime.EnableWindow(false); } //禁用它
	else { m_ctl_cleartime.SetCheck(false); }

}

void CQQllkDlg::OnGameTop()
{
	UpdateData(true);
	gametop = m_gametop;
	if (m_gametop)
	{
		HWND gameh = ::FindWindow(NULL, gameCaption);
		if (gameh == 0) { return; } //没有找到游戏窗口
		  //让游戏窗口置顶
		::SetWindowPos(gameh, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}//窗口置顶
	else
	{
		HWND gameh = ::FindWindow(NULL, gameCaption);
		if (gameh == 0) { return; } //没有找到游戏窗口
		  //让游戏窗口置顶
		::SetWindowPos(gameh, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}//窗口置顶


}

void CQQllkDlg::OnClearAll()
{
	int chessnum = ReadChessNum();

	// TODO: Add your control notification handler code here
	while (chessnum != 0)
	{
		ClearPiar();
		//	Sleep(1); //0x001166E0 棋子数=0时退出
		chessnum = ReadChessNum();
	}
}




