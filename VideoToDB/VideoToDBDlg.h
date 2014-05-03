
// VideoToDBDlg.h : 头文件
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

// CVideoToDBDlg 对话框
class CVideoToDBDlg : public CDialogEx
{
// 构造
public:
	CVideoToDBDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIDEOTODB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void DrawPicToHDC(IplImage *img, UINT ID);
	CString LoadVideo();
	void Capture(CString VideoPath);
	IplImage* GetHis(CString FramePath);
};
