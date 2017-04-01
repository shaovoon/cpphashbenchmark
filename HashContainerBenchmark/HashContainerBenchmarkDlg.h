
// HashContainerBenchmarkDlg.h : header file
//

#pragma once
#include "PaintGraph.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "GraphStatic.h"
#include "LoadDll.h"

#define WM_BENCHMARK_DONE (WM_USER+1)

enum BenchType
{
	map,
	multimap,
	set,
	multiset
};

// CHashContainerBenchmarkDlg dialog
class CHashContainerBenchmarkDlg : public CDialogEx
{
// Construction
public:
	CHashContainerBenchmarkDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HASHCONTAINERBENCHMARK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	bool SavePngFile(Gdiplus::Bitmap* pBmp, const wchar_t* pszFile);
	bool GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	bool EnumDlls();
	bool LoadDlls();
	bool DestroyDlls();
	LRESULT OnBenchmarkDone(WPARAM wParam, LPARAM lParam);
	bool InitializeData();


	bool m_bIsMapPopulated;
	bool m_bIsMultiMapPopulated;
	bool m_bIsSetPopulated;
	bool m_bIsMultiSetPopulated;

	BenchType m_BenchType;
	PaintGraph m_Graph;
	HANDLE m_hMutex;

	std::vector<std::wstring> m_vecDllPaths;
	std::vector<LoadDll*> m_vecDlls;

	std::vector<UINT> m_vecTimeTaken;
	std::vector<std::wstring> m_vecTestName;

	std::vector<std::wstring> m_vecEngDict;
	std::vector<CString> m_vecEngDictCString;

	volatile UINT m_nDoneCnt;
	volatile UINT m_nCurrentProgress;



// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBenchmark();
	afx_msg void OnBnClickedBtnSaveGraph();
	CComboBox m_cboBenchmarkType;
	CEdit m_edtTotalSearchCnt;
	CEdit m_edtRandomSeed;
	CProgressCtrl m_progressCtrl;
	CGraphStatic m_staticGraph;
	afx_msg void OnDestroy();
	CButton m_btnBenchmark;
	CButton m_btnSaveGraph;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_btnGenerateSeed;
	afx_msg void OnBnClickedBtnGenSeed();
};
