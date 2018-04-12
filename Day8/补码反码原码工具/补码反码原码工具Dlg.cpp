
// 补码反码原码工具Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "补码反码原码工具.h"
#include "补码反码原码工具Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//转换3种形式的函数
/*
负数的原码 = 补码取反 + 1
正数的原码==补码==反码
计算机中的数值都是以补码形式存储的,所以直接按照这个步骤将每位的1或0算出来即可
*/
void yuanMaFunction(int number, char *arr) {
	printf("%d\n",number);
	int mask = 1 << 31;
	if (number < 0) {
		//原码等于补码取反+1
		number = ~number + 1;
		//将符号位更改为1标识是个负数
		number = number | mask;
	}
	for (int i = 0; i < 32; i++) {
		//当最高位相与为1时,其值的补码肯定是个负数,所以要判断是否不等于0,不能判断大于0
		if ((number & mask) != 0) {
			arr[i] = '1';
		}
		else {
			arr[i] = '0';
		}
		number <<= 1;
	}
}
/*
负数的反码 = 补码 - 1
正数的原码==补码==反码
计算机中的数值都是以补码形式存储的,所以直接按照这个步骤将每位的1或0算出来即可
*/
void fanMaFunction(int number, char *arr) {
	int mask = 1 << 31;
	if (number < 0) {
		number -= 1;
	}
	for (int i = 0; i < 32; i++) {
		if ((number & mask) != 0) {
			arr[i] = '1';
		}
		else {
			arr[i] = '0';
		}
		number <<= 1;
	}
}
/*
计算机中的数值都是以补码形式存储的,所以直接将每位的1或0算出来即可
*/
void buMaFunction(int number, char *arr) {
	int mask = 1 << 31;
	for (int i = 0; i < 32; i++) {
		if ((number & mask) != 0) {
			arr[i] = '1';
		}
		else {
			arr[i] = '0';
		}
		number <<= 1;
	}
}

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


// C补码反码原码工具Dlg 对话框



C补码反码原码工具Dlg::C补码反码原码工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C补码反码原码工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT5, numberEdit);
	DDX_Control(pDX, IDC_EDIT6, yuanMaEdit);
	DDX_Control(pDX, IDC_EDIT7, fanMaEdit);
	DDX_Control(pDX, IDC_EDIT8, buMaEdit);
}

BEGIN_MESSAGE_MAP(C补码反码原码工具Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C补码反码原码工具Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C补码反码原码工具Dlg 消息处理程序

BOOL C补码反码原码工具Dlg::OnInitDialog()
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

void C补码反码原码工具Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C补码反码原码工具Dlg::OnPaint()
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
HCURSOR C补码反码原码工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C补码反码原码工具Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int number = 0;
	CStringA numberStr;
	char yuanMaArr[33] = { 0 };
	char fanMaArr[33] = { 0 };
	char buMaArr[33] = { 0 };

	numberEdit.GetWindowTextA(numberStr);
	//CString跟char *是一样的,所以可以将CString通过sscanf()转换成其他类型
	sscanf(numberStr, "%d", &number);

	//调用转换函数,将结果存储在对应的数组里面
	yuanMaFunction(number, yuanMaArr);
	fanMaFunction(number, fanMaArr);
	buMaFunction(number, buMaArr);

	yuanMaEdit.SetWindowTextA(yuanMaArr);
	buMaEdit.SetWindowTextA(buMaArr);
	fanMaEdit.SetWindowTextA(fanMaArr);
}
