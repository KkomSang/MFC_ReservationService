
// ReservationDlg.h: 헤더 파일
//

#pragma once


// CReservationDlg 대화 상자
class CReservationDlg : public CDialogEx
{
// 생성입니다.
public:
	CReservationDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESERVATION_DIALOG };
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
	static const UINT_PTR TIMER_ID = 1;
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_rList;
//	CString m_dCount;
//	CString m_pCount;
	CString m_rName;
	CString m_rPhone;
	CString m_PorD;
	CString m_rCount;
	CString m_rMenu;
//	COleDateTime m_rDate;
//	COleDateTime m_rTime;
	afx_msg void OnLvnItemchangedrlist(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_rtime;
	afx_msg void OnClickedButtonRes();
	CString m_rDate;
	afx_msg void OnClickedButtonDel();
	CString m_rAsk;
	int m_pCount;
	int m_dCount;
	afx_msg void OnItemchangedRlist(NMHDR* pNMHDR, LRESULT* pResult);
	int select;
	CString m_now;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedAsk();
};
