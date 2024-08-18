
// MallocSpeedTestDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MallocSpeedTest.h"
#include "MallocSpeedTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CMallocSpeedTestDlg ダイアログ



CMallocSpeedTestDlg::CMallocSpeedTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MALLOCSPEEDTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMallocSpeedTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EXECUTE, m_CtrlButtonExec);
	DDX_Control(pDX, IDC_EDIT_TRIAL, m_CtrlEditTrial);
	DDX_Control(pDX, IDC_EDIT_LOOP, m_CtrlEditLoop);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_CtrlEditSize);
	DDX_Control(pDX, IDC_EDIT_MALLOC, m_CtrlEditMalloc);
	DDX_Control(pDX, IDC_EDIT_NEW, m_CtrlEditNew);
	DDX_Control(pDX, IDC_EDIT_ALLOCA, m_CtrlEditAlloca);
	DDX_Control(pDX, IDC_EDIT_MALLOCA, m_CtrlEditMalloca);
}

BEGIN_MESSAGE_MAP(CMallocSpeedTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, &CMallocSpeedTestDlg::OnBnClickedButtonExecute)
END_MESSAGE_MAP()


// CMallocSpeedTestDlg メッセージ ハンドラー

BOOL CMallocSpeedTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMallocSpeedTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMallocSpeedTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMallocSpeedTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void TryMalloc(const int size) {
	char* data = (char*)malloc(size);
	free(data);
}

void TryNew(const int size) {
	char* data = new char[size];
	delete[] data;
}

void TryAlloca(const int size) {
	__try {
		char* data = (char*)_alloca(size);
	}
	__except ((GetExceptionCode() == STATUS_STACK_OVERFLOW) ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		MessageBox(NULL, _T("Stack overflow in _alloca()"), _T("MallocSpeedTest"), MB_OK);
		exit(-1);
	}
}

void TryMalloca(const int size) {
	__try {
		char* data = (char*)_malloca(size);
		_freea(data);
	}
	__except ((GetExceptionCode() == STATUS_STACK_OVERFLOW) ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		MessageBox(NULL, _T("Stack overflow in _malloca()"), _T("MallocSpeedTest"), MB_OK);
		exit(-1);
	}
}

void Test(void (*func)(const int), const int loop, const int size, LARGE_INTEGER &time)
{
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);
	for (int i = 0; i < loop; i++) {
		func(size);
	}
	QueryPerformanceCounter(&end);
	time.QuadPart += end.QuadPart - start.QuadPart;
}

void CMallocSpeedTestDlg::OnBnClickedButtonExecute()
{
	m_CtrlEditMalloc.SetWindowText(_T(""));
	m_CtrlEditNew.SetWindowText(_T(""));
	m_CtrlEditAlloca.SetWindowText(_T(""));
	m_CtrlEditMalloca.SetWindowText(_T(""));

	m_CtrlEditLoop.EnableWindow(FALSE);
	m_CtrlEditTrial.EnableWindow(FALSE);
	m_CtrlEditSize.EnableWindow(FALSE);
	m_CtrlButtonExec.EnableWindow(FALSE);

	LARGE_INTEGER tMalloc, tNew, tAlloca, tMalloca;
	tMalloc.QuadPart = tNew.QuadPart = tAlloca.QuadPart = tMalloca.QuadPart = 0;

	int loop, trial, size;
	CString buff;
	m_CtrlEditTrial.GetWindowText(buff);
	trial = _ttoi(buff);
	m_CtrlEditLoop.GetWindowText(buff);
	loop = _ttoi(buff);
	if (loop == 0 || trial == 0) {
		MessageBox(_T("loop or trial is 0. please set a number."));
		return;
	}
	m_CtrlEditSize.GetWindowText(buff);
	size = _ttoi(buff);

	for (int i = 0; i < trial; i++) {
		Test(TryMalloc, loop, size, tMalloc);
		Test(TryNew, loop, size, tNew);
		Test(TryAlloca, loop, size, tAlloca);
		Test(TryMalloca, loop, size, tMalloca);
	}

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	buff.Format(_T("%f"), ((double)tMalloc.QuadPart) / freq.QuadPart);
	m_CtrlEditMalloc.SetWindowText(buff);
	buff.Format(_T("%f"), ((double)tNew.QuadPart) / freq.QuadPart);
	m_CtrlEditNew.SetWindowText(buff);
	buff.Format(_T("%f"), ((double)tAlloca.QuadPart) / freq.QuadPart);
	m_CtrlEditAlloca.SetWindowText(buff);
	buff.Format(_T("%f"), ((double)tMalloca.QuadPart) / freq.QuadPart);
	m_CtrlEditMalloca.SetWindowText(buff);

	m_CtrlEditLoop.EnableWindow(TRUE);
	m_CtrlEditTrial.EnableWindow(TRUE);
	m_CtrlEditSize.EnableWindow(TRUE);
	m_CtrlButtonExec.EnableWindow(TRUE);
}
