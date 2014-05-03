
// VideoToDBDlg.h : ͷ�ļ�
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

// CVideoToDBDlg �Ի���
class CVideoToDBDlg : public CDialogEx
{
// ����
public:
	CVideoToDBDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIDEOTODB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
