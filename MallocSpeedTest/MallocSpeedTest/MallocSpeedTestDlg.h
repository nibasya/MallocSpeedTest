
// MallocSpeedTestDlg.h : ヘッダー ファイル
//

#pragma once


// CMallocSpeedTestDlg ダイアログ
class CMallocSpeedTestDlg : public CDialogEx
{
// コンストラクション
public:
	CMallocSpeedTestDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MALLOCSPEEDTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_CtrlButtonExec;
	CEdit m_CtrlEditLoop;
	CEdit m_CtrlEditTrial;
	CEdit m_CtrlEditSize;
	CEdit m_CtrlEditMalloc;
	CEdit m_CtrlEditNew;
	CEdit m_CtrlEditAlloca;
	CEdit m_CtrlEditMalloca;
	afx_msg void OnBnClickedButtonExecute();
};
