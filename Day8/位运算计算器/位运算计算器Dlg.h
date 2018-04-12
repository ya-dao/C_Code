
// 位运算计算器Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// C位运算计算器Dlg 对话框
class C位运算计算器Dlg : public CDialogEx
{
// 构造
public:
	C位运算计算器Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit parameter1Edit;
	CEdit parameter2Edit;
	CEdit resultEdit;
	CButton addButton;
	CButton substractButton;
	CButton multiplyButton;
	CButton divisionButton;
	CButton remainderButton;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
