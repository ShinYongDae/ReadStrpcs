
// ReadStrpcsDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ReadStrpcs.h"
#include "ReadStrpcsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadStrpcsDlg ��ȭ ����



CReadStrpcsDlg::CReadStrpcsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READSTRPCS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadStrpcsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadStrpcsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadStrpcsDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CReadStrpcsDlg �޽��� ó����

BOOL CReadStrpcsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CReadStrpcsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CReadStrpcsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CReadStrpcsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CReadStrpcsDlg::FileBrowse(CString& sPath)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	static TCHAR BASED_CODE szFilter[] = _T("Mst Files (*.bin)|*.bin|All Files (*.*)|*.*||");

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12�� Win2k Style�� ���̾�α� �ڽ��� Open��.

													   // Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}


void CReadStrpcsDlg::AllocPolygonRgnData(CPoint**& PolygonPoints, int nCornerNum, int PieceRgnNum)
{
	int i;
	CPoint	**PolygonPointsLocal = NULL;

	FreePolygonRgnData(PolygonPointsLocal);

	PolygonPointsLocal = (CPoint **)malloc(sizeof(CPoint*) * MAX_PIECE_RGN_NUM);
	int nRefinePieceNum = max(1, PieceRgnNum);
	for (i = 0; i < nRefinePieceNum; i++)
		PolygonPointsLocal[i] = (CPoint *)malloc(sizeof(CPoint) * nCornerNum);

	for (i = nRefinePieceNum; i < MAX_PIECE_RGN_NUM; i++)
	{
		PolygonPointsLocal[i] = NULL;
	}

	PolygonPoints = PolygonPointsLocal;
}

void CReadStrpcsDlg::FreePolygonRgnData(CPoint	**PolygonPoints)
{
	int i;
	if (PolygonPoints != NULL)
	{
		for (i = 0; i < MAX_PIECE_RGN_NUM; i++)
		{
			if (PolygonPoints[i] != NULL)
			{
				free(PolygonPoints[i]);
				PolygonPoints[i] = NULL;
			}
		}

		free(PolygonPoints);
		PolygonPoints = NULL;
	}
}

CString sName[25] =
{
	_T("nFrameSize"),								// 0.
	_T("PieceRgnNum"), 								// 1.
	_T("nCornerNum"),								// 2.
	_T("nDummy[0]"), 								// 3.	
	_T("nDummy[1]"), 								// 4	
	_T("nDummy[2]"), 								// 5.		
	_T("nDummy[3]"), 								// 6.	
	_T("nDummy[4]"), 								// 7.	
	_T("FrameRgnID.nId"),						 	// 8.
	_T("FrameRgnID.Row"),							// 9.
	_T("FrameRgnID.Col"),							// 10.
	_T("nDummy[5]"),								// 11.
	_T("FrameRgnPix.iStartX"),						// 12.
	_T("FrameRgnPix.iStartY"),						// 13.
	_T("FrameRgnPix.iEndX"),						// 14.
	_T("FrameRgnPix.iEndY"),						// 15.
	_T("FrameRgnPix.FMirror"),						// 16.
	_T("FrameRgnPix.FRotate"),						// 17.
	_T("nPieceNum"), 								// 18.
	_T("PieceRgnPix.nId"),							// 19.
	_T("PieceRgnPix.Row"),							// 20.
	_T("PieceRgnPix.Col"),							// 21.
	_T("nDummy[6]"),								// 22.
	_T("PieceRgnPix.PolygonPoint"),					// 23. 
	_T("PieceRgnPix.FRotate")						// 24.
};

BOOL CReadStrpcsDlg::LoadStrpcsFromCam(CString& sPath, CString& sData)
{
	CString str = _T("");
	sData = _T("");
	int nN = 0;

	short FrameRgnNum;
	int PieceRgnNum;
	int nCornerNum;
	int nDummy[MAX_PATH];
	int nPieceNum[MAX_PATH];

	REGIONS_FRAME FrameRgnPix[MAX_FRAME_RGN_NUM];
	REGIONS_FRAME_ID FrameRgnID[MAX_FRAME_RGN_NUM];
	REGIONS_PIECE_2 PieceRgnPix[MAX_PIECE_RGN_NUM];

	//TCHAR		FileNCam[1024];
	CString		strFileNCam;
	CFileFind	find;

	// 1. Find File "strpcs.rgn"

	if (!find.FindFile(sPath))
	{
		AfxMessageBox(_T("StrPcs.bin������ ã�����߽��ϴ�."));
		return(FALSE);
	}

	// 2. Read Strip & Piece Info
	int		i, j, k, Dummy;
	int		PieceNum, PieceCount;
	CFile	file;
	TCHAR	FileNLoc[1024];
	_stprintf(FileNLoc, _T("%s"), sPath);

	if (!file.Open(FileNLoc, CFile::modeRead))
	{
		if (!file.Open(FileNLoc, CFile::modeRead))
		{
			AfxMessageBox(_T("ķ�����Ϳ� �ǽ����������� Open���� ���߽��ϴ�."));
			return(FALSE);
		}
	}

	int nFrameSize = 0;

	file.Read((void *)&nFrameSize, sizeof(int));
	FrameRgnNum = nFrameSize;

	file.Read((void *)&PieceRgnNum, sizeof(int));
	file.Read((void *)&nCornerNum, sizeof(int));
	file.Read((void *)&nDummy[0], sizeof(int));	// reserved
	file.Read((void *)&nDummy[1], sizeof(int));	// reserved
	file.Read((void *)&nDummy[2], sizeof(int));	// reserved
	file.Read((void *)&nDummy[3], sizeof(int));	// reserved
	file.Read((void *)&nDummy[4], sizeof(int));	// reserved

	str.Format(_T("%s: %d"), sName[nN], FrameRgnNum); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], PieceRgnNum); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], nCornerNum); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], nDummy[0]); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], nDummy[1]); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], nDummy[2]); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], nDummy[3]); nN++;
	sData += str;
	sData += _T("\r\n");

	str.Format(_T("%s: %d"), sName[nN], nDummy[4]); nN++;
	sData += str;
	sData += _T("\r\n");

	// Init. Buffers
	sData += _T("\r\n");
	for (i = 0; i < FrameRgnNum; i++)
	{
		FrameRgnPix[i].iStartX = 0;
		FrameRgnPix[i].iStartY = 0;
		FrameRgnPix[i].iEndX = 0;
		FrameRgnPix[i].iEndY = 0;
		FrameRgnPix[i].FRotate = 0;
		FrameRgnPix[i].FMirror = 0;
		FrameRgnID[i].Col = -1;
		FrameRgnID[i].Row = -1;
	}

	for (i = 0; i < MAX_PIECE_RGN_NUM; i++)
	{
		PieceRgnPix[i].iStartX = 0;
		PieceRgnPix[i].iStartY = 0;
		PieceRgnPix[i].iEndX = 0;
		PieceRgnPix[i].iEndY = 0;
		PieceRgnPix[i].FRotate = 0;
		PieceRgnPix[i].FMirror = 0;

		//PieceRgnID[i].nHeight = 0; //140204lgh
		//PieceRgnID[i].nWidth = 0; //140204 lgh

		PieceRgnPix[i].Col = -1;
		PieceRgnPix[i].Row = -1;
	}

	if (PieceRgnNum > MAX_PIECE_RGN_NUM)
	{
		file.Close();
		AfxMessageBox(_T("ķ�����Ϳ��� ������ �ǽ� ������ �ִ�ġ�� �ʰ��߽��ϴ�."));
		return FALSE;
	}

	//start for previous pcs info.
	CRect rtFrm(10000, 10000, 0, 0);
	double fData1, fData2, fData3, fData4;
	long lTop = 0;
	int nCol = 0, nRow = 0;
	int Size = 0;
	int nPieceRgnNum = 0;

	//double mmPxl = MasterInfo.dPixelSize / 1000.0; // [mm]
	//end for previous pcs info.


	CPoint	**PolygonPoints = NULL;
	AllocPolygonRgnData(PolygonPoints, nCornerNum, PieceRgnNum);

	PieceCount = 0;
	for (j = 0; j < FrameRgnNum; j++)
	{
		// 4. Set Strip Info.
		file.Read((void *)&FrameRgnID[j].nId, sizeof(int));						// Strip ID

		//file.Read((void *)&nDummy, sizeof(int));			// reserved
		//file.Read((void *)&nDummy, sizeof(int));			// reserved
		file.Read((void *)&FrameRgnID[j].Row, sizeof(int));						// Row
		file.Read((void *)&FrameRgnID[j].Col, sizeof(int));						// Col

		file.Read((void *)&nDummy[5], sizeof(int));							// Rotation Info (0 : 0  1 : 90  2 : 180  3 : 270 [Degree])
		file.Read((void *)&(FrameRgnPix[j]), sizeof(REGIONS_FRAME));			// (int * 6)

		// 5. Set Piece Info.
		file.Read((void *)&nPieceNum[j], sizeof(int));


		str.Format(_T("%d-%s: %d"), j, sName[nN + 0], FrameRgnID[j].nId);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 1], FrameRgnID[j].Row);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 2], FrameRgnID[j].Col);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 3], nDummy[5]);
		sData += str;
		sData += _T("\r\n");

		/*
		int iStartX, iStartY;
		int iEndX, iEndY;
		int FMirror;	//0 : ���� 1 : ���Ϲ̷�  2 : �¿�̷�
		int FRotate;	//0 : 0��  1 : 90��  2 : 180��  3 : 270��
		*/
		str.Format(_T("%d-%s: %d"), j, sName[nN + 4], FrameRgnPix[j].iStartX);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 5], FrameRgnPix[j].iStartY);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 6], FrameRgnPix[j].iEndX);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 7], FrameRgnPix[j].iEndY);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 8], FrameRgnPix[j].FMirror);
		sData += str;
		sData += _T("\r\n");

		str.Format(_T("%d-%s: %d"), j, sName[nN + 9], FrameRgnPix[j].FRotate);
		sData += str;
		sData += _T("\r\n");


		str.Format(_T("%d-%s: %d"), j, sName[nN + 10], nPieceNum[j]);
		sData += str;
		sData += _T("\r\n");

		if(nPieceNum[j] > 0)
			sData += _T("\r\n");

		for (i = 0; i < nPieceNum[j]; i++)
		{
			file.Read((void *)&PieceRgnPix[i + PieceCount].nId, sizeof(int));	// Piece ID
			file.Read((void *)&PieceRgnPix[i + PieceCount].Row, sizeof(int));	// Row
			file.Read((void *)&PieceRgnPix[i + PieceCount].Col, sizeof(int));	// Col
			file.Read((void *)&nDummy[6 + i + PieceCount], sizeof(int));		// Rotation Info (0 : 0  1 : 90  2 : 180  3 : 270 [Degree])

			str.Format(_T("%d-%s: %d"), i, sName[nN + 11], PieceRgnPix[i + PieceCount].nId);
			sData += str;
			sData += _T("\r\n");

			str.Format(_T("%d-%s: %d"), i, sName[nN + 12], PieceRgnPix[i + PieceCount].Row);
			sData += str;
			sData += _T("\r\n");

			str.Format(_T("%d-%s: %d"), i, sName[nN + 13], PieceRgnPix[i + PieceCount].Col);
			sData += str;
			sData += _T("\r\n");

			str.Format(_T("%d-%s: %d"), i, sName[nN + 14], nDummy[6 + i + PieceCount]);
			sData += str;
			sData += _T("\r\n");

			////////////////////////////////////////////////////////////////////////////////////////////////
			// Set Piece position
			Dummy = sizeof(CPoint);
			file.Read((void *)PolygonPoints[i + PieceCount], sizeof(CPoint)*nCornerNum);
			file.Read((void *)&(PieceRgnPix[i + PieceCount].FRotate), sizeof(int));

			// Set PieceRgnPix
			PieceRgnPix[i + PieceCount].iStartX = PolygonPoints[i + PieceCount][0].x;
			PieceRgnPix[i + PieceCount].iStartY = PolygonPoints[i + PieceCount][0].y;
			PieceRgnPix[i + PieceCount].iEndX = PolygonPoints[i + PieceCount][0].x;
			PieceRgnPix[i + PieceCount].iEndY = PolygonPoints[i + PieceCount][0].y;
			for (k = 0; k < nCornerNum; k++)
			{
				PieceRgnPix[i + PieceCount].iStartX = min(PieceRgnPix[i + PieceCount].iStartX, PolygonPoints[i + PieceCount][k].x);
				PieceRgnPix[i + PieceCount].iStartY = min(PieceRgnPix[i + PieceCount].iStartY, PolygonPoints[i + PieceCount][k].y);
				PieceRgnPix[i + PieceCount].iEndX = max(PieceRgnPix[i + PieceCount].iEndX, PolygonPoints[i + PieceCount][k].x);
				PieceRgnPix[i + PieceCount].iEndY = max(PieceRgnPix[i + PieceCount].iEndY, PolygonPoints[i + PieceCount][k].y);

				str.Format(_T("%d-%s: %d, %d"), i, sName[nN + 15], PolygonPoints[i + PieceCount][k].x, PolygonPoints[i + PieceCount][k].y);
				sData += str;
				sData += _T("\r\n");
			}

			str.Format(_T("%d-%s: %d"), i, sName[nN + 16], PieceRgnPix[i + PieceCount].FRotate);
			sData += str;
			sData += _T("\r\n");
		}
		sData += _T("\r\n");
		PieceCount += nPieceNum[j];

	}// for(j = 0; j < FrameRgnNum; j++)
	sData += _T("\r\n");
	nN = nN + 17;

	 //start for previous pcs info.
	nPieceRgnNum = PieceRgnNum;

	if (nPieceRgnNum > 0)
	{
		//if (pPcsRgn)
		//	delete pPcsRgn;
		//pPcsRgn = new CPcsRgn(nPieceRgnNum);
	}
	else
	{
		file.Close();
		Size = 0;
		FreePolygonRgnData(PolygonPoints);

		AfxMessageBox(_T("ķ�����Ϳ��� ������ �ǽ� ������ �����ϴ�."));
		return(FALSE);
	}

	for (i = 0; i < nPieceRgnNum; i++)
	{

		fData1 = (double)PieceRgnPix[i].iStartX;
		fData2 = (double)PieceRgnPix[i].iStartY;
		fData3 = (double)PieceRgnPix[i].iEndX;
		fData4 = (double)PieceRgnPix[i].iEndY;
		//fData1 = (double)PieceRgnPix[i].iStartX * mmPxl;
		//fData2 = (double)PieceRgnPix[i].iStartY * mmPxl;
		//fData3 = (double)PieceRgnPix[i].iEndX * mmPxl;
		//fData4 = (double)PieceRgnPix[i].iEndY * mmPxl;
		//pPcsRgn->pPcs[i] = CRect(fData1, fData2, fData3, fData4);// (left, top, right, bottom)
		//pPcsRgn->pCenter[i] = CfPoint((fData1 + fData3) / 2.0, (fData2 + fData4) / 2.0);

		//if (i > 0)
		//{
		//	if (lTop == pPcsRgn->pPcs[i].top)
		//		nCol++;
		//}
		//else
		//	lTop = pPcsRgn->pPcs[i].top;

		//if (pPcsRgn->pPcs[i].left < rtFrm.left)
		//	rtFrm.left = pPcsRgn->pPcs[i].left;
		//if (pPcsRgn->pPcs[i].top < rtFrm.top)
		//	rtFrm.top = pPcsRgn->pPcs[i].top;
		//if (pPcsRgn->pPcs[i].right > rtFrm.right)
		//	rtFrm.right = pPcsRgn->pPcs[i].right;
		//if (pPcsRgn->pPcs[i].bottom > rtFrm.bottom)
		//	rtFrm.bottom = pPcsRgn->pPcs[i].bottom;
	}

	//nCol++;

	//pPcsRgn->nCol = nCol;
	//pPcsRgn->nRow = nPieceRgnNum / nCol;

	double dWidth = rtFrm.right - rtFrm.left;
	double dHeight = rtFrm.bottom - rtFrm.top;
	double dMarginW = dWidth * 0.05;
	double dMarginH = dHeight * 0.05;
	double dMargin = (dMarginW > dMarginH) ? dMarginH : dMarginW;

	//pPcsRgn->rtFrm.left = rtFrm.left - dMargin;
	//pPcsRgn->rtFrm.top = rtFrm.top - dMargin;
	//pPcsRgn->rtFrm.right = rtFrm.right + dMargin;
	//pPcsRgn->rtFrm.bottom = rtFrm.bottom + dMargin;
	//end for previous pcs info.

	file.Close();

	FreePolygonRgnData(PolygonPoints);
	return TRUE;
}

void CReadStrpcsDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STATIC_PATH)->SetWindowText(sPath);

	CString sData = _T("");
	if (!LoadStrpcsFromCam(sPath, sData))
		AfxMessageBox(_T("LoadStripRgnFromCam failed!"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sData);
}
