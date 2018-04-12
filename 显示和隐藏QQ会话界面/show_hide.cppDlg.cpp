
// show_hide.cppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "show_hide.cpp.h"
#include "show_hide.cppDlg.h"
#include "afxdialogex.h"
#include <Windows.h>

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


// Cshow_hidecppDlg 对话框



Cshow_hidecppDlg::Cshow_hidecppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOW_HIDECPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cshow_hidecppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cshow_hidecppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &Cshow_hidecppDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cshow_hidecppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &Cshow_hidecppDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &Cshow_hidecppDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &Cshow_hidecppDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON7, &Cshow_hidecppDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON8, &Cshow_hidecppDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON9, &Cshow_hidecppDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// Cshow_hidecppDlg 消息处理程序

BOOL Cshow_hidecppDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cshow_hidecppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cshow_hidecppDlg::OnPaint()
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
HCURSOR Cshow_hidecppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cshow_hidecppDlg::OnBnClickedButton2()
{
	//隐藏PanDownload界面
	// TODO: 在此添加控件通知处理程序代码
	HWND window = FindWindowA("CMainWnd", "Pan Download");
	if (window != NULL) {
		::ShowWindow(window, 0);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton1()
{
	//显示PanDownload界面
	// TODO: 在此添加控件通知处理程序代码
	HWND window = FindWindowA("CMainWnd", "Pan Download");
	if (window != NULL) {
		::ShowWindow(window, 1);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//显示QQ会话界面
	HWND window = FindWindowA("TXGuiFoundation", "表情包");
	if (window != NULL) {
		::ShowWindow(window, 1);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//隐藏QQ会话界面
	// TODO: 在此添加控件通知处理程序代码
	HWND window = FindWindowA("TXGuiFoundation", "表情包");
	if (window != NULL) {
		::ShowWindow(window, 0);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton7()
{
	HWND mainWindow = FindWindowA(NULL, "AnyDesk");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 0);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton8()
{
	HWND mainWindow = FindWindowA(NULL, "AnyDesk");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 1);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND mainWindow = FindWindowA("ConsoleWindowClass", "Tomcat");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 0);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND mainWindow = FindWindowA("ConsoleWindowClass", "Tomcat");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 1);
	}
	else {
		MessageBoxA(0, "该程序未启动", "提示", 0);
	}
}
