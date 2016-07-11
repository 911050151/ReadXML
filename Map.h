#pragma once
#include "explorer1.h"


// Map 对话框

class Map : public CDialogEx
{
	DECLARE_DYNAMIC(Map)

public:
	Map(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Map();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_explorer;
};
