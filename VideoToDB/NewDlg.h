#pragma once


// NewDlg 对话框

class NewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewDlg)

public:
	NewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NewDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
