
// VideoToDBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoToDB.h"
#include "VideoToDBDlg.h"
#include "afxdialogex.h"
#include"NewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CVideoToDBDlg 对话框




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


// CVideoToDBDlg 消息处理程序

BOOL CVideoToDBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVideoToDBDlg::OnPaint()
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
HCURSOR CVideoToDBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVideoToDBDlg::OnBnClickedButton1()
{
	CString VideoPath;
	IplImage *image=NULL; 
	// TODO: 在此添加控件通知处理程序代码
	/*
	NewDlg aa;
	aa.DoModal();
	*/
	//原始图像
	if(image) cvReleaseImage(&image);
	//VideoPath=LoadVideo();
	//image = cvLoadImage(VideoPath,1); //显示图片
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
cimg.CopyOf( img ); // 复制图片
cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
ReleaseDC( pDC );
}

CString CVideoToDBDlg::LoadVideo()
{
	CString m_strPicPath=NULL;
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.avi;*.mp4)|*.avi;*.mp4|All Files(*.*)|*.*|"),NULL);//弹出选择图片对话框
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
	p[1]=60;//质量值，0-100，100表示质量最高
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
 
	/** H 分量划分为16个等级，S分量划分为8个等级 */
	int h_bins = 8, s_bins = 8;
	int hist_size[] = {h_bins, s_bins};

	/**定义hs量值数组*/
	float HSVNum [8][8];

	/** H 分量的变化范围 */
	float h_ranges[] = { 0, 180 }; 
 
	/** S 分量的变化范围*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };
 
	/** 输入图像转换到HSV颜色空间 */
	cvCvtColor( src, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
 
	/** 创建直方图，二维, 每个维度上均分 */
	CvHistogram * hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
	/** 根据H,S两个平面数据统计直方图 */
	cvCalcHist( planes, hist, 0, 0 );
 
	/** 获取直方图统计的最大值，用于动态显示直方图 */
	float max_value;
	cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );
 
 
	/** 设置直方图显示图像 */
	int height = 240;
	int width = (h_bins*s_bins*6);
	IplImage* hist_img = cvCreateImage( cvSize(width,height), 8, 3 );
	cvZero( hist_img );
 
	/** 用来进行HSV到RGB颜色转换的临时单位图像 */
	IplImage * hsv_color = cvCreateImage(cvSize(1,1),8,3);
	IplImage * rgb_color = cvCreateImage(cvSize(1,1),8,3);
	int bin_w = width / (h_bins * s_bins);
	for(int h = 0; h < h_bins; h++)
	{
		for(int s = 0; s < s_bins; s++)
		{
			int i = h*s_bins + s;
			/** 获得直方图中的统计次数，计算显示在图像中的高度 */
			float bin_val = cvQueryHistValue_2D( hist, h, s );
			int intensity = cvRound(bin_val*height/max_value);
			HSVNum[h][s]=bin_val*height/max_value;
			/** 获得当前直方图代表的颜色，转换成RGB用于绘制 */
			
			cvSet2D(hsv_color,0,0,cvScalar(h*180.f / h_bins,s*255.f/s_bins,255,0));
			cvCvtColor(hsv_color,rgb_color,CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color,0,0);
 
			cvRectangle( hist_img, cvPoint(i*bin_w,height),
				cvPoint((i+1)*bin_w,height - intensity),
				color, -1, 8, 0 );
				

		}
	}
 
	/**直方图数据显示*/
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

	/**直方图比较函数

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

