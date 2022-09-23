
// ReadStrpcsDlg.h : ��� ����
//

#pragma once


#define MAX_PIECE_NODE_X_NUM	600		// 130319 jsy edit
#define MAX_PIECE_NODE_Y_NUM	600

#define MAX_FRAME_RGN_NUM		1000		// Maximum number of Strip regions
#define MAX_STRIP_X_NUM			10			//2012.08.07 hyk
#define MAX_STRIP_Y_NUM			10			//2012.08.07 hyk
#define MAX_PIECE_RGN_NUM		(MAX_PIECE_NODE_X_NUM * MAX_PIECE_NODE_Y_NUM)		// Maximum number of Cell regions

typedef struct {
	int iStartX, iStartY;
	int iEndX, iEndY;
	int FMirror;	//0 : ���� 1 : ���Ϲ̷�  2 : �¿�̷�
	int FRotate;	//0 : 0��  1 : 90��  2 : 180��  3 : 270��
} REGIONS_FRAME;


typedef struct {
	int nId;
	int Col;
	int Row;
} REGIONS_FRAME_ID;


typedef struct
{
	int iStartX, iStartY;
	int iEndX, iEndY;
	int FMirror;	//0 : Defult 1 : Up to Down Mirroring  2 : Left to Right Mirroring
	int FRotate;	//0 : 0  1 : 90  2 : 180  3 : 270 [Degree]
} REGIONS_PIECE;

typedef struct {
	int nId;
	int iStartX, iStartY;
	int iEndX, iEndY;
	int FMirror;	//0 : ���� 1 : ���Ϲ̷�  2 : �¿�E̷?
	int FRotate;	//0 : 0��  1 : 90��  2 : 180��  3 : 270��
	int Row;
	int Col;
} REGIONS_PIECE_2;


// for DTS

#define PATH_ORDERING_Mk	_T("C:\\R2RSet\\Test\\WriteOrederingMkRotate90ccw.txt")
#define MAX_PCE_ROW			100
#define MAX_PCE_COL			100
#define MAX_STRIP			4
#define MAX_STRIP_NUM		4
#define MAX_PCS				10000
#define MAX_NodeNumY		100
#define MAX_NodeNumX		100

struct _Point {
	double dX, dY;

	_Point()
	{
		dX = 0.0; dY = 0.0;
	}
};

struct _Rect {
	double dLeft, dTop, dRight, dBottom;

	_Rect()
	{
		dLeft = 0.0; dTop = 0.0; dRight = 0.0; dBottom = 0.0;
	}
};

struct _MasterPiece {
	int nMstPcsIdx, nMstStripIdx;
	int nMstStripRow, nMstStripCol;
	int nMstPcsRow, nMstPcsCol;
	_Point MkPos;
	_Rect Area;

	_MasterPiece()
	{
		nMstPcsIdx = -1; nMstStripIdx = -1;		// from 0 ~
		nMstStripRow = -1; nMstStripCol = -1;	// from 0 ~
		nMstPcsRow = -1; nMstPcsCol = -1;		// from 0 ~
		MkPos.dX = 0.0; MkPos.dY = 0.0;			// [mm]
		Area.dLeft = 0.0; Area.dTop = 0.0; Area.dRight = 0.0; Area.dBottom = 0.0; // [mm]
	}
};

struct _MasterStrip {
	int nMstStripIdx;
	int nTotalPiece;
	int nTotalPieceRow, nTotalPieceCol;
	_Rect Area;
	_MasterPiece Piece[MAX_NodeNumY][MAX_NodeNumX]; // Piece[Row][Col] 

	_MasterStrip()
	{
		nMstStripIdx = -1;
		nTotalPiece = 0;
		nTotalPieceRow = 0; nTotalPieceCol = 0;
		Area.dLeft = 0.0; Area.dTop = 0.0; Area.dRight = 0.0; Area.dBottom = 0.0; // [mm]
	}
};

struct _MasterPanel {
	int nTotalStrip; // Strip Index : 0 ~ (TotalStrip-1)
	int nTotalStripRow, nTotalStripCol;
	int nTotalPiece, nPcsCorner;
	int nTotalAlignPos;
	_Point AlignPos[4];
	_Point PinPos;
	_Rect Area;
	CString sPathPinImg, sPathPcsImg, sPathAlignImg[4]; // * CadlinkImg�� �˻�� Cell Image��.
	CString sPath2ptAlignAndMkPos, sPath4ptAlignAndMkPos;
	CString sPathPinPos;								// [ORIGIN COORD] (����): PX, PY ; (�˻翵�� �»�): MX, MY
														// [PANEL INFO] (�˻翵�� W, H): InspectionWidth, InspectionHeight

	_MasterStrip Strip[MAX_STRIP];	// Strip[Row] - CamMaster�� Row, Col ������
	_MasterPiece Piece[MAX_PCS];	// CamMaster�� �ε��� ������

	_MasterPanel()
	{
		nTotalStrip = 0; // Strip Index : 0 ~ (TotalStrip-1)
		nTotalStripRow = 0; nTotalStripCol = 0;
		nTotalPiece = 0;	nPcsCorner = 0;
		nTotalAlignPos = 0;
		AlignPos[0].dX = 0.0; AlignPos[1].dX = 0.0; AlignPos[2].dX = 0.0; AlignPos[3].dX = 0.0; // [mm]
		AlignPos[0].dY = 0.0; AlignPos[1].dY = 0.0; AlignPos[2].dY = 0.0; AlignPos[3].dY = 0.0; // [mm]
		PinPos.dX = 0.0; PinPos.dY = 0.0; // [mm]
		Area.dLeft = 0.0; Area.dTop = 0.0; Area.dRight = 0.0; Area.dBottom = 0.0; // [mm]
		sPathPinImg = _T(""); sPathPcsImg = _T("");
		sPathAlignImg[0] = _T(""); sPathAlignImg[1] = _T(""); sPathAlignImg[2] = _T(""); sPathAlignImg[3] = _T("");
		sPath2ptAlignAndMkPos = _T(""); sPath4ptAlignAndMkPos = _T(""); sPathPinPos = _T("");
	}
};


// CReadStrpcsDlg ��ȭ ����
class CReadStrpcsDlg : public CDialogEx
{
	_MasterPanel MstPnl;

	short FrameRgnNum;
	int PieceRgnNum;
	int m_nRow, m_nCol;
	REGIONS_FRAME_ID FrameRgnID[MAX_FRAME_RGN_NUM];
	int nPieceNum[MAX_STRIP];
	REGIONS_PIECE_2 PieceRgnPix[MAX_PIECE_RGN_NUM];

	int m_MkOrder2PnlPcsIdx[MAX_PIECE_RGN_NUM];			// ��ŷ������ �ǽ� �ε��� (�»�ܺ��� ������׷� ��ŷ)
	int m_PnlPcsIdx2MkOrder[MAX_PIECE_RGN_NUM];			// ķ������ �ǽ� �ε����� ��ŷ����

	int GetTotPcs();
	void SetShotRowCol(int nR, int nC);
	void GetShotRowCol(int& nR, int& nC);
	void InitOrederingMk();
	CString WriteOrederingMk();
	BOOL GetMkMatrix(int nPcsId, int &nC, int &nR);	// nC:0~ , nR:0~
	void SetMasterPanelInfo();
	void StringToChar(CString str, char *szStr);
	char* StringToChar(CString str); // char* returned must be deleted... 

	BOOL FileBrowse(CString& sPath);
	BOOL LoadStrpcsFromCam(CString& sPath, CString& sData);

	void AllocPolygonRgnData(CPoint**& PolygonPoints, int nCornerNum, int PieceRgnNum);
	void FreePolygonRgnData(CPoint	**PolygonPoints);

// �����Դϴ�.
public:
	CReadStrpcsDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READSTRPCS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
