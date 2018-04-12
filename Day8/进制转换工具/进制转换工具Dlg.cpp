
// 进制转换工具Dlg.cpp : 实现文件
//
#include "stdafx.h"
#include "进制转换工具.h"
#include "进制转换工具Dlg.h"
#include "afxdialogex.h"

#include<stdio.h>
#include<stdlib.h>
/*
通过模拟计算一个数的二进制,八进制,十六进制
*/
/*
10 % 2 = 0	10 / 2 = 5

5  % 2 = 1	5  / 2 = 2

2  % 2 = 0	2 / 2 = 1
1  % 2 = 1	1 / 2 = 0
*/
void binary(int number, char *arr) {
	int i = 31;
	arr[32] = '\0';
	for (; i >= 0; i--) {
		if (number > 0) {
			arr[i] = number % 2 + '0';
		}
		else {
			arr[i] = '0';
		}
		number /= 2;
	}
}
void octal(int number, char* arr) {
	int i = 10;
	arr[11] = '\0';
	for (; i >= 0; i--) {
		if (number > 0) {
			arr[i] = number % 8 + '0';
		}
		else {
			arr[i] = '0';
		}
		number /= 8;
	}
}
void hex(int number, char *arr) {
	int i = 7;
	arr[8] = '\0';
	for (; i >= 0; i--) {
		if (number % 16 >= 10) {
			arr[i] = number % 16 - 10 + 'A';
		}
		else {
			arr[i] = number % 16 + '0';
		}

		number /= 16;
	}
}

void recursiveBinary(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 2, arr, index - 1);
		arr[index] = number % 2 + '0';
	}
}

void recursiveOctal(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 8, arr, index - 1);
		arr[index] = number % 8 + '0';
	}
}

void recursiveHex(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 16, arr, index - 1);
		if (number % 16 >= 10) {
			arr[index] = number % 16 - 10 + 'A';
		}
		arr[index] = number % 16 + '0';
	}
}

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


// C进制转换工具Dlg 对话框



C进制转换工具Dlg::C进制转换工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C进制转换工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, numberEdit);
	DDX_Control(pDX, IDC_EDIT1, binaryEdit);
	DDX_Control(pDX, IDC_EDIT2, octalEdit);
	DDX_Control(pDX, IDC_EDIT3, hexEdit);
}

BEGIN_MESSAGE_MAP(C进制转换工具Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C进制转换工具Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C进制转换工具Dlg 消息处理程序

BOOL C进制转换工具Dlg::OnInitDialog()
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

void C进制转换工具Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C进制转换工具Dlg::OnPaint()
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
HCURSOR C进制转换工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C进制转换工具Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//先获取数据输入框中的值
	CString numberString;

	int number = 0;
	char binaryArray[33] = { 0 };
	char octalArray[12] = { 0 };
	char hexArray[9] = { 0 };

	numberEdit.GetWindowTextA(numberString);
	sscanf(numberString,"%d",&number);

	binary(number, binaryArray);
	octal(number, octalArray);
	hex(number, hexArray);



	binaryEdit.SetWindowTextA(binaryArray);
	octalEdit.SetWindowTextA(octalArray);
	hexEdit.SetWindowTextA(hexArray);
}
