
// ReadStrpcs.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CReadStrpcsApp:
// �� Ŭ������ ������ ���ؼ��� ReadStrpcs.cpp�� �����Ͻʽÿ�.
//

class CReadStrpcsApp : public CWinApp
{
public:
	CReadStrpcsApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CReadStrpcsApp theApp;