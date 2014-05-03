
// VideoToDBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoToDB.h"
#include "VideoToDBDlg.h"
#include "afxdialogex.h"
#include"NewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoToDBDlg �Ի���




CVideoToDBDlg::CVideoToDBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoToDBDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoToDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVideoToDBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVideoToDBDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CVideoToDBDlg ��Ϣ�������

BOOL CVideoToDBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVideoToDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVideoToDBDlg::OnPaint()
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
HCURSOR CVideoToDBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVideoToDBDlg::OnBnClickedButton1()
{
	CString VideoPath;
	IplImage *image=NULL; 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	NewDlg aa;
	aa.DoModal();
	*/
	//ԭʼͼ��
	if(image) cvReleaseImage(&image);
	//VideoPath=LoadVideo();
	//image = cvLoadImage(VideoPath,1); //��ʾͼƬ
	//DrawPicToHDC(image, IDC_STATIC_KEYFRAME);
	Capture(LoadVideo());



}

void CVideoToDBDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
CDC *pDC = GetDlgItem(ID)->GetDC();
HDC hDC= pDC->GetSafeHdc();
CRect rect;
GetDlgItem(ID)->GetClientRect(&rect);
CvvImage cimg;
cimg.CopyOf( img ); // ����ͼƬ
cimg.DrawToHDC( hDC, &rect ); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
ReleaseDC( pDC );
}

CString CVideoToDBDlg::LoadVideo()
{
	CString m_strPicPath=NULL;
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.avi;*.mp4)|*.avi;*.mp4|All Files(*.*)|*.*|"),NULL);//����ѡ��ͼƬ�Ի���
	dlg.m_ofn.lpstrTitle=_T("open Image");
	if(dlg.DoModal()!=IDOK)
	return m_strPicPath;;
	m_strPicPath = dlg.GetPathName();
	m_strPicPath.Replace(_T("//"),_T("////"));
	return m_strPicPath;
}

void CVideoToDBDlg::Capture(CString VideoPath)
{
	int p[3];
	p[0]=CV_IMWRITE_JPEG_QUALITY;
	p[1]=60;//����ֵ��0-100��100��ʾ�������
	p[2]=0;
	IplImage *frame=NULL;
	CvCapture* capture=NULL;
	capture=cvCaptureFromAVI(VideoPath);
	while(capture)
	{
		frame=cvQueryFrame(capture);
		cvSaveImage("demo.jpg",frame,p);
		DrawPicToHDC(frame, IDC_STATIC_KEYFRAME);
		//DrawPicToHDC(GetHis("demo.jpg"), IDC_STATIC_KEYHIS);
		//DrawPicToHDC(frame, IDC_STATIC_KEYHIS);
		
		GetHis("demo.jpg");
		//Sleep(20);
	}
}

IplImage* CVideoToDBDlg::GetHis(CString FramePath)
{
	IplImage* src= cvLoadImage(FramePath);
	IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* planes[] = { h_plane, s_plane };
 
	/** H ��������Ϊ16���ȼ���S��������Ϊ8���ȼ� */
	int h_bins = 8, s_bins = 8;
	int hist_size[] = {h_bins, s_bins};

	/**����hs��ֵ����*/
	float HSVNum [8][8];

	/** H �����ı仯��Χ */
	float h_ranges[] = { 0, 180 }; 
 
	/** S �����ı仯��Χ*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };
 
	/** ����ͼ��ת����HSV��ɫ�ռ� */
	cvCvtColor( src, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
 
	/** ����ֱ��ͼ����ά, ÿ��ά���Ͼ��� */
	CvHistogram * hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
	/** ����H,S����ƽ������ͳ��ֱ��ͼ */
	cvCalcHist( planes, hist, 0, 0 );
 
	/** ��ȡֱ��ͼͳ�Ƶ����ֵ�����ڶ�̬��ʾֱ��ͼ */
	float max_value;
	cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );
 
 
	/** ����ֱ��ͼ��ʾͼ�� */
	int height = 240;
	int width = (h_bins*s_bins*6);
	IplImage* hist_img = cvCreateImage( cvSize(width,height), 8, 3 );
	cvZero( hist_img );
 
	/** ��������HSV��RGB��ɫת������ʱ��λͼ�� */
	IplImage * hsv_color = cvCreateImage(cvSize(1,1),8,3);
	IplImage * rgb_color = cvCreateImage(cvSize(1,1),8,3);
	int bin_w = width / (h_bins * s_bins);
	for(int h = 0; h < h_bins; h++)
	{
		for(int s = 0; s < s_bins; s++)
		{
			int i = h*s_bins + s;
			/** ���ֱ��ͼ�е�ͳ�ƴ�����������ʾ��ͼ���еĸ߶� */
			float bin_val = cvQueryHistValue_2D( hist, h, s );
			int intensity = cvRound(bin_val*height/max_value);
			HSVNum[h][s]=bin_val*height/max_value;
			/** ��õ�ǰֱ��ͼ�������ɫ��ת����RGB���ڻ��� */
			
			cvSet2D(hsv_color,0,0,cvScalar(h*180.f / h_bins,s*255.f/s_bins,255,0));
			cvCvtColor(hsv_color,rgb_color,CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color,0,0);
 
			cvRectangle( hist_img, cvPoint(i*bin_w,height),
				cvPoint((i+1)*bin_w,height - intensity),
				color, -1, 8, 0 );
				

		}
	}
 
	/**ֱ��ͼ������ʾ*/
		for(int h = 0; h < h_bins; h++)
	{
		for(int s = 0; s < s_bins; s++)
		{
			//printf("%0.2f\n",HSVNum[h][s]);
			//char HisData[20];
			//sprintf_s(HisData,"%s",HSVNum[h][s]);
			//GetDlgItem(IDC_STATIC_T1)->SetWindowText(HisData);
		}
	}

	/**ֱ��ͼ�ȽϺ���

for(int h = 0; h < h_bins; h++)
	{
		for(int s = 0; s < s_bins; s++)
		{
			
		}
	}

	
		/*
	cvNamedWindow( "Source", 1 );
	cvShowImage( "Source", src );
 
	cvNamedWindow( "H-S Histogram", 1 );
	cvShowImage( "H-S Histogram", hist_img );
 */char HisData[20];
			//sprintf_s(HisData,"%s",HSVNum[5][5]);
			GetDlgItem(IDC_STATIC_T1)->SetWindowText("fgfg");
	DrawPicToHDC(hist_img, IDC_STATIC_KEYHIS);
	cvReleaseImage(&src);
	cvReleaseImage(&hsv);
	cvReleaseImage(&h_plane);
	cvReleaseImage(&s_plane);
	cvReleaseImage(&v_plane);
	cvReleaseImage(&hsv_color);
	cvReleaseImage(&rgb_color);
	cvReleaseImage(&hist_img);
	 return hist_img;
}

