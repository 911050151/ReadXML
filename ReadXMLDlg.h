// ReadXMLDlg.h : ͷ�ļ�
//
#if !defined(AFX_XMLPARSERSAMPLEDLG_H__C87A91B1_CC73_4A30_9CA6_623A050839FC__INCLUDED_)
#define AFX_XMLPARSERSAMPLEDLG_H__C87A91B1_CC73_4A30_9CA6_623A050839FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// CReadXMLDlg �Ի���
class CReadXMLDlg : public CDialogEx
{
// ����
public:
	CReadXMLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_READXML_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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