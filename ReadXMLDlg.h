// ReadXMLDlg.h : 头文件
//
#if !defined(AFX_XMLPARSERSAMPLEDLG_H__C87A91B1_CC73_4A30_9CA6_623A050839FC__INCLUDED_)
#define AFX_XMLPARSERSAMPLEDLG_H__C87A91B1_CC73_4A30_9CA6_623A050839FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// CReadXMLDlg 对话框
class CReadXMLDlg : public CDialogEx
{
// 构造
public:
	CReadXMLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_READXML_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedRead();
	CString FilePathFileName;
	CString FileName;
	afx_msg void OnBnClickedWritehtml();
};
#endif