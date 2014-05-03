// NewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoToDB.h"
#include "NewDlg.h"
#include "afxdialogex.h"


// NewDlg 对话框

IMPLEMENT_DYNAMIC(NewDlg, CDialogEx)

NewDlg::NewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(NewDlg::IDD, pParent)
{

}

NewDlg::~NewDlg()
{
}

void NewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewDlg, CDialogEx)
END_MESSAGE_MAP()


// NewDlg 消息处理程序
