
// ReadXMLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadXML.h"
#include "ReadXMLDlg.h"
#include "afxdialogex.h"
#include"msxml2.h"
#include"Map.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import   "msxml3.dll"
using namespace MSXML2;
// CReadXMLDlg 对话框

CString FilePath;//全局变量，源文件路径,不包括文件名

CReadXMLDlg::CReadXMLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadXMLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	FileName = _T("");
}

void CReadXMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadXMLDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Browse, &CReadXMLDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_Read, &CReadXMLDlg::OnBnClickedRead)
	ON_BN_CLICKED(IDC_WriteHtml, &CReadXMLDlg::OnBnClickedWritehtml)
END_MESSAGE_MAP()


// CReadXMLDlg 消息处理程序

BOOL CReadXMLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadXMLDlg::OnPaint()
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
HCURSOR CReadXMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadXMLDlg::OnBnClickedBrowse()
{
	CFileDialog fileDlg(TRUE,_T("xml"),NULL,0,L"所有文件(*.*)|*.*||",this);
	if(IDOK==fileDlg.DoModal())
	{
		FilePathFileName=fileDlg.GetPathName();
		SetDlgItemText(IDC_FilePath,FilePathFileName);
	}
	FileName=fileDlg.GetFileName();
	FilePath=FilePathFileName;
	FilePath.Replace(FileName,L"");
}

void CReadXMLDlg::OnBnClickedRead()
{
	USES_CONVERSION;
	CFile ReadXml;
	CoInitialize(NULL);   
	MSXML2::IXMLDOMDocumentPtr XMLDom;        
	if (!SUCCEEDED(XMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument30))))
		MessageBox(L"创建DOMDocument对象失败，请确认安装MSXMLParser组件!");	   
	if(!XMLDom->load((_bstr_t)FilePathFileName))
	{
		MessageBox(L"没有找到文件，程序被强制结束！");
		ExitProcess(0);	
	}
	MSXML2::IXMLDOMElementPtr  NodeChild;   
	NodeChild=(MSXML2::IXMLDOMElementPtr)(XMLDom->selectSingleNode("//trkseg"));
	VARIANT varVal;
	NodeChild->get_nodeTypedValue(&varVal);
	MSXML2::IXMLDOMNodeListPtr NodeList;
	MSXML2::IXMLDOMNodePtr Node;
	NodeList = (MSXML2::IXMLDOMNodeListPtr)NodeChild->selectNodes("trkpt");
	long nodeCount = NodeList->Getlength();
	ReadXml.Open(FilePath+"ReadXML.csv",CFile::modeCreate|CFile::modeWrite);
	for (int i = 0;i <nodeCount;i++)
	{
		if (!SUCCEEDED(NodeList->get_item(i, &Node))) 
			continue;
		CString Date=NULL, Number=NULL;
		VARIANT ability;
		Node->get_nodeTypedValue(&ability);
		Date=ability;
		Date.Replace(L"T",L",");
		Date.Replace(L"Z",L"");
		Number.Format(L"%d",i+1);
		ReadXml.Write(W2A(Number),Number.GetLength());
		ReadXml.Write(",",1);
		ReadXml.Write(T2A(Date),Date.GetLength());
		ReadXml.Write(",",1);
		MSXML2::IXMLDOMNamedNodeMapPtr AllNature=NULL;   
		MSXML2::IXMLDOMNodePtr   OneNode;        
		Node->get_attributes(&AllNature);   
		long   Count;
		AllNature->get_length(&Count);   
		for(int j=0; j<Count; j++)   
		{ 
			if (!SUCCEEDED(AllNature->get_item(j,&OneNode))) 
				continue;			
			ReadXml.Write((char*)(_bstr_t)OneNode->text,OneNode->text.length());
			ReadXml.Write(",",1);
		}
		ReadXml.Write(T2A(_T("\r\n")),2);	
	}
	ReadXml.Close();
	MessageBox(L"操作完毕，已存放至源文件目录下。");
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

/*
	
	MSXML2::IXMLDOMDocumentPtr;//XML文档类型
	
	MSXML2::IXMLDOMElementPtr;//单个元素类
	
	MSXML2::IXMLDOMNodePtr;//单个节点类
	
	MSXML2::IXMLDOMNodeListPtr;//所有子节点类

	MSXML2::IXMLDOMNamedNodeMapPtr;//所有属性类

	get_item(索引号，单个节点类型变量)；//获得指定节点方法
	get_childNodes();//获得所有子节点
	put_text((_bstr_t)"内容")；//写入单个节点文本内容
	XMLNODE->text;//获得单个节点的文本内容属性
	XMLNODEEATT->text;//获得单个属性的内容属性
	XMLNODE->nodeName；//节点名的属性为
	*/

void CReadXMLDlg::OnBnClickedWritehtml()
{
	USES_CONVERSION;
	Map WinMap;
	int place=0;
	CString str_SourceFile=NULL;
	CString lng,lat;
	char *Source_tmp;
	char *chr_html_1;
	char *chr_html_2;
	CFile SourceFile;
	if(!SourceFile.Open(FilePathFileName,CFile::modeRead))
		MessageBox(L"您没有选择文件，请先选择文件！");
	CFile html(FilePath+"Map_API.html",CFile::modeCreate|CFile::modeWrite);
	CFile html_1(L"html_1.txt",CFile::modeRead);
	CFile html_2(L"html_2.txt",CFile::modeRead);
	Source_tmp=new char[SourceFile.GetLength()];
	chr_html_1=new char[html_1.GetLength()];
	chr_html_2=new char[html_2.GetLength()];
	SourceFile.Read(Source_tmp,SourceFile.GetLength());
	str_SourceFile=Source_tmp;
	html_1.Read(chr_html_1,html_1.GetLength());
	html_2.Read(chr_html_2,html_2.GetLength());
	html.Write(chr_html_1,html_1.GetLength());
	place=str_SourceFile.Find(L"trkpt",0);
	while(place<(SourceFile.GetLength()-130))         //new BMap.Point(111.699438, 40.793076),
	{
		lng=str_SourceFile.Mid(place+27,10);
		lat=str_SourceFile.Mid(place+11,9);
		html.Write(T2A(_T("\r\n")),2);
		html.Write("new BMap.Point(",15);
		html.Write(T2A(lng),10);
		html.Write(",",1);
		html.Write(T2A(lat),9);
		html.Write("),",2);
		place+=94;
	}
	html.Write(T2A(_T("\r\n")),2);
	html.Write(chr_html_2,html_2.GetLength());
	SourceFile.Close();
	html_1.Close();
	html_2.Close();
	html.Close();
	WinMap.DoModal();
}
