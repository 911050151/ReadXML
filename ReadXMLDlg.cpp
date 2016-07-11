
// ReadXMLDlg.cpp : ʵ���ļ�
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
// CReadXMLDlg �Ի���

CString FilePath;//ȫ�ֱ�����Դ�ļ�·��,�������ļ���

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


// CReadXMLDlg ��Ϣ�������

BOOL CReadXMLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadXMLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReadXMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadXMLDlg::OnBnClickedBrowse()
{
	CFileDialog fileDlg(TRUE,_T("xml"),NULL,0,L"�����ļ�(*.*)|*.*||",this);
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
		MessageBox(L"����DOMDocument����ʧ�ܣ���ȷ�ϰ�װMSXMLParser���!");	   
	if(!XMLDom->load((_bstr_t)FilePathFileName))
	{
		MessageBox(L"û���ҵ��ļ�������ǿ�ƽ�����");
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
	MessageBox(L"������ϣ��Ѵ����Դ�ļ�Ŀ¼�¡�");
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

/*
	
	MSXML2::IXMLDOMDocumentPtr;//XML�ĵ�����
	
	MSXML2::IXMLDOMElementPtr;//����Ԫ����
	
	MSXML2::IXMLDOMNodePtr;//�����ڵ���
	
	MSXML2::IXMLDOMNodeListPtr;//�����ӽڵ���

	MSXML2::IXMLDOMNamedNodeMapPtr;//����������

	get_item(�����ţ������ڵ����ͱ���)��//���ָ���ڵ㷽��
	get_childNodes();//��������ӽڵ�
	put_text((_bstr_t)"����")��//д�뵥���ڵ��ı�����
	XMLNODE->text;//��õ����ڵ���ı���������
	XMLNODEEATT->text;//��õ������Ե���������
	XMLNODE->nodeName��//�ڵ���������Ϊ
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
		MessageBox(L"��û��ѡ���ļ�������ѡ���ļ���");
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
