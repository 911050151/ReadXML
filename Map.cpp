// Map.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadXML.h"
#include "Map.h"
#include "afxdialogex.h"
#include"ReadXMLDlg.h"

// Map 对话框
extern CString FilePath;
IMPLEMENT_DYNAMIC(Map, CDialogEx)

Map::Map(CWnd* pParent /*=NULL*/)
	: CDialogEx(Map::IDD, pParent)
{

}

Map::~Map()
{
}

void Map::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_explorer);
	m_explorer.Navigate(FilePath+L"Map_API.html",NULL,NULL,NULL,NULL);
}


BEGIN_MESSAGE_MAP(Map, CDialogEx)
END_MESSAGE_MAP()


// Map 消息处理程序
