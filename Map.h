#pragma once
#include "explorer1.h"


// Map �Ի���

class Map : public CDialogEx
{
	DECLARE_DYNAMIC(Map)

public:
	Map(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Map();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_explorer;
};
