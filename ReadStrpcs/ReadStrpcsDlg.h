
// ReadStrpcsDlg.h : 헤더 파일
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
	int FMirror;	//0 : 원본 1 : 상하미러  2 : 좌우미러
	int FRotate;	//0 : 0도  1 : 90도  2 : 180도  3 : 270도
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
	int FMirror;	//0 : 원본 1 : 상하미러  2 : 좌퓖E肩?
	int FRotate;	//0 : 0도  1 : 90도  2 : 180도  3 : 270도
	int Row;
	int Col;
} REGIONS_PIECE_2;


// CReadStrpcsDlg 대화 상자
class CReadStrpcsDlg : public CDialogEx
{
	BOOL FileBrowse(CString& sPath);
	BOOL LoadStrpcsFromCam(CString& sPath, CString& sData);

	void AllocPolygonRgnData(CPoint**& PolygonPoints, int nCornerNum, int PieceRgnNum);
	void FreePolygonRgnData(CPoint	**PolygonPoints);

// 생성입니다.
public:
	CReadStrpcsDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READSTRPCS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
