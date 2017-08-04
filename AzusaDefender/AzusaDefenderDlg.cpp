
// AzusaDefenderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AzusaDefender.h"
#include "AzusaDefenderDlg.h"
#include "afxdialogex.h"
#include "DiaA.h"
#include "DiaB.h"
#include "DiaC.h"
#include "DiaD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAzusaDefenderDlg 对话框



CAzusaDefenderDlg::CAzusaDefenderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AZUSADEFENDER_DIALOG, pParent),
	m_IsWindowHide(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAzusaDefenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_ctrlTab);
}

BEGIN_MESSAGE_MAP(CAzusaDefenderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CAzusaDefenderDlg 消息处理程序

BOOL CAzusaDefenderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ctrlTab.InsertItem(0, L"我的管家");
	m_ctrlTab.InsertItem(1, L"任务管理器");
	m_ctrlTab.InsertItem(2, L"服务管理器");
	m_ctrlTab.InsertItem(3, L"病毒查杀");
	//给子窗口指针赋值
	m_ctrlTab.m_Dia[0] = new CDiaA();
	m_ctrlTab.m_Dia[1] = new CDiaB();
	m_ctrlTab.m_Dia[2] = new CDiaC();
	m_ctrlTab.m_Dia[3] = new CDiaD();
	//创建子窗口
	m_ctrlTab.m_Dia[0]->Create(IDD_DIALOG1, &m_ctrlTab);
	m_ctrlTab.m_Dia[1]->Create(IDD_DIALOG2, &m_ctrlTab);
	m_ctrlTab.m_Dia[2]->Create(IDD_DIALOG4, &m_ctrlTab);
	m_ctrlTab.m_Dia[3]->Create(IDD_DIALOG5, &m_ctrlTab);
	//控制子窗口的大小
	CRect rc;
	m_ctrlTab.GetClientRect(rc);
	rc.DeflateRect(2, 23, 2, 2);
	m_ctrlTab.m_Dia[0]->MoveWindow(rc);
	m_ctrlTab.m_Dia[1]->MoveWindow(rc);
	m_ctrlTab.m_Dia[2]->MoveWindow(rc);
	m_ctrlTab.m_Dia[3]->MoveWindow(rc);
	//显示第一个窗口
	m_ctrlTab.m_Dia[0]->ShowWindow(SW_SHOW);
	m_ctrlTab.m_Dia[1]->ShowWindow(SW_HIDE);
	m_ctrlTab.m_Dia[2]->ShowWindow(SW_HIDE);
	m_ctrlTab.m_Dia[3]->ShowWindow(SW_HIDE);

	//注册热键
	::RegisterHotKey(this->GetSafeHwnd(), 0Xa001, MOD_CONTROL | MOD_SHIFT | MOD_ALT, 'k');
	::RegisterHotKey(this->GetSafeHwnd(), 0Xa001, MOD_CONTROL | MOD_SHIFT | MOD_ALT, 'K');
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAzusaDefenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAzusaDefenderDlg::OnPaint()
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
HCURSOR CAzusaDefenderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAzusaDefenderDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nHotKeyId)
	{
	case 0xa001:
		if (m_IsWindowHide)
		{
			ShowWindow(SW_HIDE);
			m_IsWindowHide = FALSE;
		}
		//显示窗口的代码
		else
		{
			ShowWindow(SW_SHOW);
			m_IsWindowHide = TRUE;
		}
		break;
	default:
		break;
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
