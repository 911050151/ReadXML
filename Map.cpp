// Map.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadXML.h"
#include "Map.h"
#include "afxdialogex.h"
#include"ReadXMLDlg.h"

// Map �Ի���
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


// Map ��Ϣ�������
