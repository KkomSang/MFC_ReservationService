
// ReservationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Reservation.h"
#include "ReservationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CReservationDlg 대화 상자



CReservationDlg::CReservationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESERVATION_DIALOG, pParent)
	, m_rName(_T(""))
	, m_rPhone(_T(""))
	, m_PorD(_T(""))
	, m_rCount(_T(""))
	, m_rMenu(_T(""))
	, m_rtime(_T(""))
	, m_rDate(_T(""))
	, m_rAsk(_T(""))
	, m_pCount(0)
	, m_dCount(0)
	, select(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReservationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_rLIST, m_rList);
	DDX_Text(pDX, IDC_rNAME, m_rName);
	DDX_Text(pDX, IDC_rPhone, m_rPhone);
	DDX_CBString(pDX, IDC_P_D, m_PorD);
	DDX_CBString(pDX, IDC_rCOUNT, m_rCount);
	DDX_CBString(pDX, IDC_rMENU, m_rMenu);
	DDX_CBString(pDX, IDC_rTIME, m_rtime);
	DDX_DateTimeCtrl(pDX, IDC_rDATE, m_rDate);
	DDX_Text(pDX, IDC_rAsk, m_rAsk);
	DDX_Text(pDX, IDC_pCount, m_pCount);
	DDX_Text(pDX, IDC_dCount, m_dCount);
	m_pCount;
	m_dCount;
	DDX_Text(pDX, IDC_NOW, m_now);
}

BEGIN_MESSAGE_MAP(CReservationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CReservationDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_rLIST, &CReservationDlg::OnLvnItemchangedrlist)
	ON_BN_CLICKED(IDC_BUTTON_res, &CReservationDlg::OnClickedButtonRes)
	ON_BN_CLICKED(IDC_BUTTON_del, &CReservationDlg::OnClickedButtonDel)
	ON_NOTIFY(HDN_ITEMCHANGED, 0, &CReservationDlg::OnItemchangedRlist)
	//ON_STN_CLICKED(ASK, &CReservationDlg::OnStnClickedAsk)
END_MESSAGE_MAP()


// CReservationDlg 메시지 처리기

// MyDialog.cpp 파일




BOOL CReservationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTimer(TIMER_ID, 1000, NULL);

	m_rList.InsertColumn(0, _T("예약번호"), LVCFMT_CENTER, 80);
	m_rList.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 70);
	m_rList.InsertColumn(2, _T("연락처"), LVCFMT_CENTER, 170);
	m_rList.InsertColumn(3, _T("유형"), LVCFMT_CENTER, 50);
	m_rList.InsertColumn(4, _T("예약 날짜"), LVCFMT_CENTER, 150);
	m_rList.InsertColumn(5, _T("예약 시간"), LVCFMT_CENTER, 100);
	m_rList.InsertColumn(6, _T("메뉴"), LVCFMT_CENTER, 200);
	m_rList.InsertColumn(7, _T("수량"), LVCFMT_CENTER, 50);
	m_rList.InsertColumn(8, _T("주소 및 요청사항"), LVCFMT_CENTER, 300);
	m_rList.SetExtendedStyle(m_rList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	((CComboBox*)GetDlgItem(IDC_P_D))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_rMENU))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_rCOUNT))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_rTIME))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_rDATE))->SetCurSel(0);
	//((CButton*)GetDlgItem(IDC_BUTTON_res))->EnableWindow(FALSE);
	//((CButton*)GetDlgItem(IDC_BUTTON_del))->EnableWindow(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CReservationDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID)
	{
	CTime currentTime = CTime::GetCurrentTime();
	m_now = currentTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	SetDlgItemText(IDC_NOW, m_now);
	}

	CDialog::OnTimer(nIDEvent);
}


void CReservationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CReservationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CReservationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReservationDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CReservationDlg::OnLvnItemchangedrlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	select = pNMLV->iItem;

	m_rName = m_rList.GetItemText(select, 1);
	m_rPhone = m_rList.GetItemText(select, 2);
	m_PorD = m_rList.GetItemText(select, 3);
	m_rDate = m_rList.GetItemText(select, 4);
	m_rtime = m_rList.GetItemText(select, 5);
	m_rMenu = m_rList.GetItemText(select, 6);
	m_rCount = m_rList.GetItemText(select, 7);
	m_rAsk = m_rList.GetItemText(select, 8);

	//((CButton*)GetDlgItem(IDC_BUTTON_del))->EnableWindow(TRUE);
	UpdateData(FALSE);

	*pResult = 0;
}


void CReservationDlg::OnClickedButtonRes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCount = m_rList.GetItemCount();
	CString strCount;
	CString pickup = (_T("포장"));
	CString delivery = (_T("배달"));

	UpdateData(TRUE);
	if (!m_rName.IsEmpty() && !m_rPhone.IsEmpty() && !m_PorD.IsEmpty() && !m_rDate.IsEmpty() && !m_rtime.IsEmpty() && !m_rMenu.IsEmpty() && !m_rCount.IsEmpty()) {
		strCount.Format(_T("%d"), nCount + 1);
		m_rList.InsertItem(nCount, strCount);
		m_rList.SetItem(nCount,1, LVIF_TEXT, m_rName, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 2, LVIF_TEXT, m_rPhone, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 3, LVIF_TEXT, m_PorD, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 4, LVIF_TEXT, m_rDate, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 5, LVIF_TEXT, m_rtime, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 6, LVIF_TEXT, m_rMenu, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 7, LVIF_TEXT, m_rCount, 0, 0, 0, 0);
		m_rList.SetItem(nCount, 8, LVIF_TEXT, m_rAsk, 0, 0, 0, 0);
		//AfxMessageBox(m_PorD);
		//AfxMessageBox(pickup);
		if (!m_PorD.Compare(pickup)) {
			m_pCount += 1;
		}
		else {
			m_dCount += 1;
		}
		m_rName.Empty();
		m_rPhone.Empty();
		m_rAsk.Empty();
		((CComboBox*)GetDlgItem(IDC_P_D))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_rMENU))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_rCOUNT))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_rTIME))->SetCurSel(0);
		((CComboBox*)GetDlgItem(IDC_rDATE))->SetCurSel(0);

		//((CButton*)GetDlgItem(IDC_BUTTON_res))->EnableWindow(FALSE);
		//((CButton*)GetDlgItem(IDC_BUTTON_del))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else {
		MessageBox(_T("모든 필수 정보를 입력하세요!"), MB_OK);
	}
}

void CReservationDlg::OnItemchangedRlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	*pResult = 0;
}


void CReservationDlg::OnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림4 처리기 코드를 추가합니다.
	CString pickup = (_T("포장"));
	CString delivery = (_T("배달"));
	if (select >= 0) {
		CString type = m_rList.GetItemText(select, 3);
		m_rList.DeleteItem(select);
		if (type.Compare(pickup) == 0) {
			m_pCount -= 1;
		}
		else {
			m_dCount -= 1;
		}
		for (int i = select-1; i < m_rList.GetItemCount(); i++) {
			CString strIndex;
			strIndex.Format(_T("%d"), i + 1);
			m_rList.SetItemText(i, 0, strIndex);
		};
		m_rName.Empty();
		m_rPhone.Empty();
		m_PorD.Empty();
		m_rDate.Empty();
		m_rtime.Empty();
		m_rMenu.Empty();
		m_rCount.Empty();
		m_rAsk.Empty();
		UpdateData(FALSE);
		select = -1;
	}
	else {
		if (m_rList.GetItemCount() <= 0) {
			MessageBox(_T("취소할 예약이 없습니다"), MB_OK);
		}
		else {
			MessageBox(_T("취소할 예약을 선택하세요"), MB_OK);
		}
	}

}
