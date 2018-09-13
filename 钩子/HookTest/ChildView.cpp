
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "HookTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

HMODULE hDllLib;
CChildView::CChildView()
{
	
}

CChildView::~CChildView()
{
	
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_APP_EXIT, &CChildView::OnAppExit)
	ON_COMMAND(ID_EDIT_UNDO, &CChildView::OnEditUndo)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



void CChildView::OnAppExit()
{
	// TODO: 在此添加命令处理程序代码
	hDllLib = LoadLibrary(L"./钩子.dll");
	FARPROC initHook = GetProcAddress(hDllLib, "initHook");
	(*initHook)();
}


void CChildView::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	FARPROC endHook = GetProcAddress(hDllLib, "endHook");
	(*endHook)();
	FreeLibrary(hDllLib);
}
