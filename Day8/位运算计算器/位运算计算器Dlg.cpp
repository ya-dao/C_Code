
// 位运算计算器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "位运算计算器.h"
#include "位运算计算器Dlg.h"
#include "afxdialogex.h"

#include<stdio.h>
#include<stdlib.h>
/*
使用位运算实现加减乘除取模
加法即两个数进行异或运算,然后通过与运算判断有无进位的情况,如果有直接左移一位即可
*/
int add(int a, int b) {
	int sum = 0;
	sum = a ^ b;
	if ((a & b) != 0) {
		sum += ((a & b) << 1);
	}
	return sum;
}
/*
5 - 3 = 2
5的补码:
0000 0101

3的原码
先将其转换成负数
0000 0011 ==>  1111 1100
再求其反码
1000 0011 ==>  1111 1100
再+1得到补码
1111 1100 ==>  1111 1101
再进行加法
*/
int substract(int a, int b) {
	int mask = 4294967295;
	int minus = 0;
	//先异或得到反码
	b ^= mask;
	//加1得到补码
	b += 1;
	minus = add(a, b);
	
	return minus;
}
/*
乘法即是多个加法
*/
int times(int a, int b) {
	int i = 0;
	int sum = a;

	for (; i < b - 1; i++) {
		sum = sum ^ a;
		if ((a & a) != 0) {
			sum += ((a & a) << 1);
		}
	}
	
	return sum;
}
/*
除法:将被除数取反+1得到其对应的负数的补码.
然后根据除数大于被除数的条件进行循环相加最后再加1
*/
int divide(int a, int b) {
	int result = 1;
	int mask = 4294967295;
	int sum = 0;
	int c = b;
	while (a > c) {
		b = c;

		b ^= mask;
		b += 1;

		sum = a ^ b;

		//必须打括号,!=的优先大于&与运算
		if ((a & b) != 0) {
			sum += ((a & b) << 1);
		}
		a = sum;
		result++;
	}

	return result;
}

/*
取余就是进行除法,将最后小于被除数的除数做为负数
*/
int remainder(int a, int b) {
	int c = b;
	int mask = 4294967295;
	int sum = 0;
	while (a >= c) {
		b = c;
		b = b ^ mask;

		sum = b ^ 1;
		if ((b & 1) != 0) {
			sum += ((b & 1) << 1);
		}

		b = sum;

		sum = a ^ b;
		if ((a & b) != 0) {
			sum += ((a & b) << 1);
		}

		a = sum;
	}
	
	return a;
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


// C位运算计算器Dlg 对话框



C位运算计算器Dlg::C位运算计算器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C位运算计算器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, parameter1Edit);
	DDX_Control(pDX, IDC_EDIT2, parameter2Edit);
	DDX_Control(pDX, IDC_EDIT3, resultEdit);
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, substractButton);
	DDX_Control(pDX, IDC_BUTTON3, multiplyButton);
	DDX_Control(pDX, IDC_BUTTON4, divisionButton);
	DDX_Control(pDX, IDC_BUTTON5, remainderButton);
}

BEGIN_MESSAGE_MAP(C位运算计算器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C位运算计算器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C位运算计算器Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C位运算计算器Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C位运算计算器Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C位运算计算器Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// C位运算计算器Dlg 消息处理程序

BOOL C位运算计算器Dlg::OnInitDialog()
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

void C位运算计算器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C位运算计算器Dlg::OnPaint()
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
HCURSOR C位运算计算器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//加法操作
void C位运算计算器Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };
	
	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = add(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//减法
void C位运算计算器Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = substract(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//乘法
void C位运算计算器Dlg::OnBnClickedButton3()
{
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = times(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//除法
void C位运算计算器Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = divide(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//求余
void C位运算计算器Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = remainder(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}
