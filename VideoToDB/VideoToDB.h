
// VideoToDB.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVideoToDBApp:
// �йش����ʵ�֣������ VideoToDB.cpp
//

class CVideoToDBApp : public CWinApp
{
public:
	CVideoToDBApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVideoToDBApp theApp;