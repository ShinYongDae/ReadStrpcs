
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


// CReadStrpcsDlg ��ȭ ����
class CReadStrpcsDlg : public CDialogEx
{
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
